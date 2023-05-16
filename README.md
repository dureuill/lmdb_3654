# lmdb_3654

C reproducer for https://github.com/meilisearch/meilisearch/issues/3654.

On a x86_64 Linux, get the `lmdb_mp_pages.c` file, then:

```
gcc lmdb_mp_pages.c -llmdb -L. -o lmdb_mp_pages
mkdir test.mdb
./lmdb_mp_pages
```

should output:
```
could not commit 5
```
(5 being `EIO`)

On a version of LMDB modified with some debug statement, I get the following additional context:

```
mp_pages=524288, size*mp_pages=2147483648
wres != wsize, wres >= 0, wres=2147479552, wsize=2147483648, n=1
```

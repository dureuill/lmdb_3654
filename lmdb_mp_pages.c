#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "lmdb.h"

int main() {
        int rc;

        size_t nb_items = 2147479553;
        void* buf = calloc(nb_items, 1);

        MDB_env* env;
        MDB_dbi dbi;
        MDB_val key = { .mv_size=1, .mv_data="a" };
        MDB_val data = { .mv_size=nb_items, .mv_data=buf };
        MDB_txn* txn;

        rc = mdb_env_create(&env);
        if (rc != 0) {
                printf("could not create env %d\n", rc);
                return 1;
        }
        rc = mdb_env_set_mapsize(env, nb_items*1000); // 2TB
        if (rc != 0) {
                printf("could not set mapsize %d\n", rc);
                return 1;
        }
        rc = mdb_env_open(env, "test.mdb", 0, S_IRWXU | S_IRWXG | S_IROTH);
        if (rc != 0) {
                printf("could not open env %d\n", rc);
                return 1;
        }
        rc = mdb_txn_begin(env, NULL, 0, &txn);
        if (rc != 0) {
                printf("could not open txn %d\n", rc);
                return 1;
        }
        rc = mdb_dbi_open(txn, NULL, MDB_CREATE, &dbi);
        if (rc != 0) {
                printf("could not open dbi %d\n", rc);
                return 1;
        }
        rc = mdb_put(txn, dbi, &key, &data, 0);
        if (rc != 0) {
                printf("could not put %d\n", rc);
                return 1;
        }
        rc = mdb_txn_commit(txn);
        if (rc != 0) {
                printf("could not commit %d\n", rc);
                return 1;
        }
        mdb_env_close(env);

        printf("success\n");
        return 0;
}

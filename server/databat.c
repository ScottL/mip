#include <my_global.h>
#include <mysql.h>

/* mysql host, user, password */
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "rootpass"



MYSQL *connection;
MYSQL_RES *result;
MYSQL_ROW row;
int num, i;


int add_user(char *name, char *pwd) {

    if (mysql_library_init(0, NULL, NULL)) {
        fprintf(stderr, "could not initialize MySQL library\n");
        exit(1);
    } 

    connection = mysql_init(NULL);
    mysql_options(connection, MYSQL_READ_DEFAULT_FILE, "/etc/mysql/my.cnf");
    if (mysql_real_connect(connection, DB_HOST, DB_USER, DB_PASS, 
                  "databat",0, NULL, 0) == NULL){
        fprintf(stderr, "%s\n", mysql_error(connection));
        exit(1);
    }

    //mysql_query(connection, "INSERT INTO users VALUES(name, pass)");

    /*
    mysql_query(connection, "INSERT INTO users VALUES('Scott Lin', '123')");
    mysql_query(connection, "INSERT INTO users VALUES('Greg Siano', '456')");
    mysql_query(connection, "INSERT INTO users VALUES('First Last', 'pwd')");
    mysql_query(connection, "INSERT INTO users VALUES('first last', 'a1-b2')");
    */

    mysql_close(connection);
    mysql_library_end();
}


int check_user(char *name, char *pwd){

    if (mysql_library_init(0, NULL, NULL)) {
        fprintf(stderr, "could not initialize MySQL library\n");
        exit(1);
    }

    connection = mysql_init(NULL);
    mysql_options(connection, MYSQL_READ_DEFAULT_FILE, "/etc/mysql/my.cnf");
    if (mysql_real_connect(connection, DB_HOST, DB_USER, DB_PASS, 
                  "databat",0, NULL, 0) == NULL){
        fprintf(stderr, "%s\n", mysql_error(connection));
        exit(1);
    }


    mysql_query(connection, "SELECT * FROM users");
    result = mysql_store_result(connection);
    num = mysql_num_fields(result);
    while(row = mysql_fetch_row(result)){
        for(i = 0; i < num; i++){
            /*Some way to check and match records in the table
            against the arguments passed in(the user logging in 
            or something */

            //test 
            printf("%s\t", row[i] ? row[i] : "NULL");
        } 
    }
    mysql_free_result(result);

    mysql_close(connection);
    mysql_library_end();
}


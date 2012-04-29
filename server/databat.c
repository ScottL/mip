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
char sql_str[1024000];

int add_user(char *fullname, char *pass, char *email) {

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
    

    //fullname, password, email, activity, date
    sprintf(sql_str, "INSERT INTO users VALUES('%s', '%s', '%s', now(), now())",
                  fullname, pass, email);
    mysql_query(connection, sql_str);


    mysql_close(connection);
    mysql_library_end();
    return -1;
}



int check_user(char *fullname, char *pass, char *email){

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
    return -1;
}



int update_user(char *fullname, char *email){
    
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
        
    sprintf(sql_str, "UPDATE writers SET activity=now() WHERE email='%s'", email);
    mysql_query(connection, sql_str);



    mysql_close(connection);
    mysql_library_end();
    return -1;
}


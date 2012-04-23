#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <my_global.h>

int main(void) {
				printf("version %s\n", mysql_get_client_info());
				return 0;
}

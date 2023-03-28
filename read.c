#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sqlite3.h>

int main(int argc, const char *argv[])
{
	sqlite3 * db;
	char * errmsg;

	char ch;
	FILE *fp;
	char * find;
	char word[32];
	char target[512];
	char buf[1024];

	fp = fopen("./dict.txt", "r");
	if (fp == NULL){
		perror("fopen");
		return -1;
	}
	if (sqlite3_open("word.db", &db) != 0){
		fprintf(stderr, "sqlite3_open err: %s\n", sqlite3_errmsg(db));
		return -1;
	}
	printf("open database ok.\n");

	while (1){
		if (fscanf(fp, "%s", word) == EOF){
			if (feof(fp)){
				printf("read success!\n");
				return 0;
			}
			else{
				perror("fscanf");
				return 0;
			}
		}
		//printf("word: %s wordlen: %d\n", word, strlen(word));

		/*跳过空白字符*/
		while (ch = fgetc(fp)){
			if (isspace(ch))
				continue;
			else
				break;
		}
		fseek(fp, -1, SEEK_CUR);

		/*读取一行剩余*/
		if (fgets(target, 256, fp) == NULL){
			if (feof(fp)){
				fprintf(stderr, "read success\n");
				fprintf(stderr, "target: %s\n", target);
				return 0;
			}
			else{
				perror("fgets");
				return -1;
			}
		}
		if (find = strchr(target, '\n'))
			*find = '\0';
		else{
			fprintf(stderr, "read target err, \"\\n\" no exist\n");
			fprintf(stderr, "target: %s\n", target);
		}
		
		sprintf(buf, "insert into word(word, info) values(\"%s\", \"%s\");", word, target);

		if (sqlite3_exec(db, buf, NULL, NULL, &errmsg) != 0){
			fprintf(stderr, "sqlite3_exec: %s\n", errmsg);
			fprintf(stderr, "buf: %s\n", buf);
			return -1;
		}
	}
	fclose(fp);
	sqlite3_close(db);
	return 0;
}

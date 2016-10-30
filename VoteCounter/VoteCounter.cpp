#include <string>
#include <map>
using namespace std;

#define MAX 50

void count_vote(map<string, int> &vote_table, FILE &file_open);
void vote_result(map<string, int> &vote_table);
int create_result_file(char *file_name, char *result);

int main()
{
 	map<string, int> vote_table;
	FILE *file_open = fopen("data\\1.input.txt", "rt");
	count_vote(vote_table, *file_open);
	vote_result(vote_table);
	return 0;
}

/*
 * @brief     Input file open and count the vote using map.
 * @param     map<string, int> &vote_table	,map for counting
 * @param     FILE &file_open				,input file.
 */
void count_vote(map<string, int> &vote_table, FILE &file_open)
{
	if(&file_open == NULL)
	{
		printf("Can not open file!\n");
	}
	else
	{
		char buffer[MAX];
		while(fgets(buffer, MAX, &file_open) != NULL)
		{
			char candidate[MAX];
			// Remove \n in buffer and scan candidate.
			if(sscanf(buffer, "%s", candidate) != 1)
				continue;
			// First, find a candidate in map.
			map<string, int>::iterator it = vote_table.find(candidate);
			// If map already has a candidate, value++.
			if(it != vote_table.end())
			{
				it->second ++;
			}
			else
			{
				// Insert new candidate.
				vote_table.insert(make_pair(candidate, 1));
			}
		}
		fclose(&file_open);
	}
}

/*
 * @brief     Search elected chairman. (one or more)
 * @param     map<string, int> &vote_table	,map for search value
 */
void vote_result(map<string, int> &vote_table)
{
	int top_vote = 0;
	char chairman[MAX*50];
	char candidate[MAX];
	memset(chairman, 0, sizeof(chairman));
	memset(candidate, 0, sizeof(candidate));

	for(map<string, int>::iterator iter = vote_table.begin(); iter != vote_table.end(); iter++ )
	{
		int vote = iter->second;

		if(top_vote < vote)
		{
			memset(chairman, 0, sizeof(chairman));
		}

		if(top_vote <= vote)
		{
			if(sscanf(iter->first.c_str(), "%s", candidate) != 1)
				continue;

			strcat(chairman, candidate);
			strcat(chairman, "\n");
			top_vote = vote;
		}
	}
	printf("%s\n", chairman);
	if(create_result_file("output.txt", chairman) == -1)
	{
		printf("Create output file fail!\n");
	}
}

/*
 * @brief     Create result file.
 * @param     char *file_name	,output file name
 * @param     char *result	    ,result of election
 */
int create_result_file(char *file_name, char *result)
{
	FILE *fp;
	fp = fopen(file_name, "wt+");
	if (fp == NULL)
		return -1;
	
	fprintf(fp, "%s", result);
	fclose(fp);
	return 0;
}
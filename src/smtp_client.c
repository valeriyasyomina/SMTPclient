#include "smtp_client.h"


static int client_running = 1;
static int watch_directory = 0;
static int file_descriptor = 0;

void signal_handler(int signum)
{	
	client_running = 0;	
	free_resources(watch_directory, file_descriptor);
}

int start_smtp_client(char* new_directory_name, char* cur_directory_name)
{
	//int r= rename("/home/lera/Desktop/maildir/new/1.txt", "/home/lera/Desktop/maildir/cur/1.txt");
	signal(SIGINT, signal_handler);

	if (!new_directory_name)
		return ERROR_DIR_NAME;

	if (!cur_directory_name)
		return ERROR_DIR_NAME;

	int watch_result = add_directory_watch(new_directory_name, WATCH_FLAGS, &watch_directory, &file_descriptor);
	if (watch_result < 0)
	{
		if (watch_result == WATCH_DIR_RESCRIPTOR_ERROR)
			close(file_descriptor);
		return watch_result;
	}
    smtp_client_main_loop(new_directory_name, cur_directory_name, file_descriptor);
	return 0;	
}

void free_resources(int watch_directory, int file_descriptor)
{
	inotify_rm_watch(file_descriptor, watch_directory);
	close(file_descriptor);
}

void smtp_client_main_loop(char* new_directory_name, char* cur_directory_name, int file_descriptor)
{
	char buffer[BUFFER_LENGTH];
	int length = 0;
	// infinite cicle for watching maildir for new letters
  //  while (client_running)
   // {

       // printf('End\n');

      //  struct string_list* list_names = get_new_files_names(new_directory_name, cur_directory_name);
       // free_string_list(list_names);

        // int a = 0;


      /*  length = read(file_descriptor, buffer, BUFFER_LENGTH);
        if (length > 0)
        {

        struct dirent **namelist = NULL;
        int files_number = scandir(new_directory_name, &namelist, NULL, alphasort);
     //   printf("files in directory %d\n", files_number);

        if (files_number > MIN_ENTITIES_NUMBER + 1)
        {
         //   printf("More files\n");
            struct string_list* files_list = get_new_files_names(namelist, files_number);
            free_string_list(files_list);
            free(namelist);
        }
        } */


    /*    while (n--) {
                       printf("%s\n", namelist[n]->d_name);
                       free(namelist[n]);
                   } */

		//printf("buffer = %s\n", buffer);
		
		// some changes in directory
    /*	if (length > 0)
		{
			char* file_name = parse_events(new_directory_name, buffer, length);
			printf("file_name = %s\n", file_name);
        }	*/
    // }
}



struct string_list* get_new_files_names(char* new_directory_name, char* cur_directory_name)
{
    struct string_list* files_names_list = create_empty_string_list();
    DIR *d = NULL;
    struct dirent *dir = NULL;
    d = opendir(new_directory_name);
    if (d)
    {
      while ((dir = readdir(d)) != NULL)
      {
          printf("%s\n", dir->d_name);

      /*    int is_cur_directory = strcmp(dir->d_name, CURRENT_DIRECTORY);
          int is_parent_directory = strcmp(dir->d_name, PARENT_DIRECTORY);
          if (is_cur_directory != 0 && is_parent_directory != 0)
          {
              char* new_file_name = get_full_filename(new_directory_name, dir->d_name);
              char* cur_file_name = get_full_filename(cur_directory_name, dir->d_name);
           //   rename(new_file_name, cur_file_name);
           //   rename_file(new_directory_name, cur_directory_name);
              files_names_list = add_string_to_list(files_names_list, dir->d_name);
              free(new_file_name);
              new_file_name = NULL;
              free(cur_file_name);
              cur_file_name = NULL;
          } */
      }
      closedir(d);
     }
    return files_names_list;
}

char* parse_events(char* new_directory_name, char* buffer, int length)
{
	int i = 0;
	char* filename = NULL;
	while (i < length) 
	{
	    struct inotify_event *event = ( struct inotify_event * ) &buffer[i];
	    if (event->len) 
	    {
	    	printf("event len = %d\n", event->len);
	      if (event->mask & IN_CREATE) 
	      {	    
	      	filename = event->name;    
	        //  printf( "The file %s was created.\n", event->name );
	      //  char* full_filename = get_full_filename(new_directory_name, event->name);
	         // printf("full filename = %s %d\n", full_filename, strlen(full_filename));
	       // struct message* message = parse_message(full_filename);
	         // free_message(message);
	        
	      }	    
	    }
		i += event->len;
  	}
  	return filename;
}



struct message* parse_message(char* file_name)
{
	// char* test = "/home/lera/Desktop/maildir/new/file.txt";
	// printf("Origin file name %s %d\n",  test, strlen(test));
	FILE* file = open_file(file_name, "r");
	if (!file)
	{
		printf("error open file\n");
		return NULL;
	}

	printf("file opened\n");

	struct message* message = create_empty_message();
	if (!message)
	{
		close_file(file);
		return NULL;
	}

	// reader_message_headers(message, file);

	return message;
}

struct message* read_message(struct message* message, FILE* file)
{
	if (!file)
		return NULL;
	char* message_data = (char*) malloc(MAX_DATA_SIZE);
	if (!message_data)
		return NULL;

	char symbol;
	int index = 0;

	while ((symbol = fgetc(file)) != EOF)
	{
		message_data[index] = symbol;
		index++;
	}
	message_data[index] = '\0';
	message->data = message_data;
	return message;

}

struct message* reader_message_headers(struct message* message, FILE* file)
{
	if (!file)
		return NULL;
	if (!message)
		return NULL;

	char buffer[MAX_BUFFER_SIZE];

	while (fgets(buffer, MAX_BUFFER_SIZE, file))
	{
		printf("Line = %s\n", buffer);
	}
	return message;
}


// adds watch to directory
// watch_directory_name: directory name
// mask: mask for watch events 
// watch_directory: watch_directory descriptor
// file_descriptor: fd of directory
// returns: error code
int add_directory_watch(char* watch_directory_name, uint32_t mask, int* watch_directory, int* file_descriptor)
{
	*file_descriptor = 0;
	*watch_directory = 0;

	if (!watch_directory_name)
		return ERROR_DIR_NAME;

	*file_descriptor = inotify_init();
	if (*file_descriptor < 0)
		return FILE_DESCRIPTOR_ERROR;

	*watch_directory = inotify_add_watch(*file_descriptor, watch_directory_name, mask);
	if (*watch_directory < 0)
		return WATCH_DIR_RESCRIPTOR_ERROR;

	return 0;
}

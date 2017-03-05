#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <sys/stat.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int main(int argc, char* argv[]){
  	//argument checking and usage information
    if (argc == 0) {
      printf("Usage Information: ./hw05 [-d file_location] [-h] [-t] [-m] <name_of_file>");
      exit(EXIT_SUCCESS);
    }

    bool opt_d = false, opt_h=false, opt_t = false, opt_m = false;
  	char* backLocation="~/backups/";
  	int opt=0;
  	char* d_arg=NULL;

  	while((opt = getopt(argc, argv, "d:htm")) != -1){
  		switch(opt) {
  			case 'd':
  				opt_d = true;
  				d_arg = strdup(optarg);
  				break;
  			case 'h':
  				opt_h = true;
  				break;
  			case 't':
  				opt_t = true;
  				break;
  			case 'm':
  				opt_m = true;
  				break;
  			default:
  				printf("Please enter options d,h,t or m.\n Option 'd' requires an argument\n");
  				return EXIT_SUCCESS;
  		}
  	}

  	if(opt_d){
  		//source: http://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c-cross-platform
  		if(access(d_arg, F_OK) != -1 ){
  			const char* backLocation = d_arg;
  			printf("Your backup director is: %s\n", backLocation);
  		}
  		else {
  			printf("BAD: Not a valid directory. Your backup folder will default to %s\n", backLocation);
  		}
	}
	if(opt_h){
		//insert opt h instructions
	}
	if(opt_t){
		//insert opt t instructions
	}
	if(opt_m){
		//instert opt m instructions
	}


  	//getopt skeleton
    
  	char buffer[EVENT_BUF_LEN];
  	int x, wd;
    char* p;
    struct inotify_event* event;
  	int fd = inotify_init();
  	
    //INITIAL BACK UP

    //fd inisilization
    if ( fd < 0 ) {
      printf("inotify init failed\n");
      exit(EXIT_FAILURE);
    }
    wd = inotify_add_watch(fd,argv[1], IN_MODIFY);
    if (wd == -1) {
      printf("wd return failure\n");
      return(EXIT_FAILURE);
    }
    while(1) {
  		x=read(fd, buffer, EVENT_BUF_LEN);
  		if ( x < 0 ) {
    		printf("read failed\n");
        exit(EXIT_FAILURE);
  		}
      for (p = buffer; p<buffer+x; ) {
        event = (struct inotify_event*) p;
        if ((event->mask & IN_MODIFY) != 0) {
          //MAKE ANOTHER COPY
        }
      }
      p += sizeof(struct inotify_event) + event->len;
  	}
    return EXIT_SUCCESS; //will not go through this.
}
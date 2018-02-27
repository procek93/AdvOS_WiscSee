#define _XOPEN_SOURCE 500
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <ftw.h>
#include <unistd.h>

/* directory names */

const char * my_strings[] = {"loc_root", "loc_dirA", "loc_dirB", "loc_dirC", "loc_dirD", "loc_dirE", "loc_dirF", "loc_dirG", "loc_dirH", "loc_dirI", "loc_dirJ"};

int cmd_rmrf( char * path);

main()
{
    DIR * dir = opendir("loc_root");
    int status = 0;


    if ( dir )
    {
        /* root exists */
        printf( "ROOT FOUND\n" );
        printf( "DELETING ROOT\n");
        
        status = cmd_rmrf( "loc_root" );
        if ( status == -1 )
        {
            printf( "ERROR: OTHER\n" );
        } 
        else
        {
            printf( "DELETED ROOT\n" );
        }
    }
    else if (ENOENT == errno)
    {
        /* directory does not exist */
    }
    else
    {
        printf( "ERROR: OTHER\n" );
    }
}

int file_unlink( const char *file_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    int status = remove(file_path);
    
    if( status )
        perror( file_path );

    return status;
}

int cmd_rmrf( char * path )
{
    return nftw(path, file_unlink, 64, FTW_DEPTH | FTW_PHYS);
}

int create_file_hierarchy_workload( void )
{
    int status = 0;
    struct stat st = {0};

    if( stat("loc_root", &st) == -1 )
    {
       status = mkdir("loc_root", 0700);

       if( status == 0)
       {
           chdir("loc_root");
       }
    }

}



/*
 * main.c
 *
 * Stand-alone utility for generating simulated pulsar pulse profiles
 * for use with the test vector generator utility, used for PST testing
 * The C code is essentially just a wrapper for auto-generated code from
 * the Matlab pulse_gen() function.
 *
 * Ian Morrison
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <float.h>
#include <complex.h>
#include <math.h>

#include "pulse_gen.h"



void usage()
{
    fprintf (stderr,
             "pulse_gen [options] parameter_file\n"
             " -v          be verbose\n\n");
}


int main (int argc, char **argv)
{
    // input parameter file
    FILE * par_fid;
    
    float val[16];
    int i;
    
    // parameters to be fetched from file
    int N;          // number of bins within a pulse period
    float noise;    // set to 0.0 for no noise, 1.0 for noise (max(S/N)=1)
    float esig;     // emission half angle (polar angle, degrees)
    float epeak;    // emission peak angle (polar angle, degrees)
    float flin;     // linear polarized fraction amplitude
    float zeta;     // observing angle (degrees) relative to rotation axis
    float alpha;    // magnetic axis (degrees) relative to rotation axis
    
    // flag to control plotting of Stokes parameters
    // (only works within Matlab, so always set to zero for stand-alone operation)
    int showplot = 0;
    
    // flag set in verbose mode
    unsigned int verbose = 0;
    
    int arg = 0;
    
    while ((arg=getopt(argc,argv,"v")) != -1)
    {
        switch (arg)
        {
            case 'v':
                verbose++;
                break;
                
            default:
                usage ();
                return 0;
        } 
    }
    
    if (verbose)
        fprintf(stderr,"\nPST Simulated Pulse Profile Generator V1\n\n");
    
    // check and parse the command line arguments
    if (argc-optind != 1)
    {
        fprintf(stderr, "\nError: parameter filename must be specified on command line\n\n");
        usage();
        exit(EXIT_FAILURE);
    }
    
    char parameter_filename[256];
    strcpy(parameter_filename, argv[optind]);
    
    struct stat buf;
    if (stat (parameter_filename, &buf) < 0)
    {
        fprintf (stderr, "Error: failed to stat parameter file [%s]: %s\n", parameter_filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    size_t filesize = buf.st_size;
    if (verbose)
        fprintf (stderr, "filesize for %s is %zu bytes\n", parameter_filename, filesize);
    
    
    /***************************/
    
    // Retrieve parameters from parameter file
    if (verbose)
        fprintf (stderr, "reading parameters from file...\n");
    
    par_fid = fopen(parameter_filename, "r");
    
    fscanf(par_fid,"N=%d noise=%f esig=%f epeak=%f flin=%f zeta=%f alpha=%f",&N,&noise,&esig,&epeak,&flin,&zeta,&alpha);
    
    fclose(par_fid);
    
    if (verbose)
        fprintf (stderr, "starting pulse profile generation...\n");

    pulse_gen(N, (double)noise, (double)esig, (double)epeak, (double)flin, (double)zeta, (double)alpha, showplot);
    
    if (verbose)
        fprintf (stderr, "pulse profile generation completed...\n");
    
    printf("Done!\n");
    
    return(1);

}


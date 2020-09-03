//лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
//лл                                                                        лл
//лл  XP32.C                                                                лл
//лл                                                                        лл
//лл  Standard XMIDI file performance utility                               лл
//лл                                                                        лл
//лл  V1.00 of  5-Aug-92: 32-bit conversion of XPLAY.C (John Lemberger)     лл
//лл  V1.01 of  1-May-93: Zortech C++ v3.1 compatibility added              лл
//лл                                                                        лл
//лл  Project: IBM Audio Interface Library for 32-bit DPMI (AIL/32)         лл
//лл   Author: John Miles                                                   лл
//лл                                                                        лл
//лл  C source compatible with Watcom C386 v9.0 or later                    лл
//лл  C source compatible with Zortech C++ v3.1 or later                    лл
//лл                                                                        лл
//лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл
//лл                                                                        лл
//лл  Copyright (C) 1991-1993 Miles Design, Inc.                            лл
//лл                                                                        лл
//лл  Miles Design, Inc.                                                    лл
//лл  6702 Cat Creek Trail                                                  лл
//лл  Austin, TX 78731                                                      лл
//лл  (512) 345-2642 / FAX (512) 338-9630 / BBS (512) 454-9990              лл
//лл                                                                        лл
//лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл

#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#include <stdint.h>

#include "ail32.h"      // Audio Interface Library API function header
#include "dll.h"

const char VERSION[] = "1.01";


static const char *const gm_names[] =
{
    "AcouGrandPiano",
    "BrightAcouGrand",
    "ElecGrandPiano",
    "Honky-tonkPiano",
    "Rhodes Piano",
    "Chorused Piano",
    "Harpsichord",
    "Clavinet",
    "Celesta",
    "Glockenspiel",
    "Music box",
    "Vibraphone",
    "Marimba",
    "Xylophone",
    "Tubular Bells",
    "Dulcimer",
    "Hammond Organ",
    "Percussive Organ",
    "Rock Organ",
    "Church Organ",
    "Reed Organ",
    "Accordion",
    "Harmonica",
    "Tango Accordion",
    "Acoustic Guitar1",
    "Acoustic Guitar2",
    "Electric Guitar1",
    "Electric Guitar2",
    "Electric Guitar3",
    "Overdrive Guitar",
    "Distorton Guitar",
    "Guitar Harmonics",
    "Acoustic Bass",
    "Electric Bass 1",
    "Electric Bass 2",
    "Fretless Bass",
    "Slap Bass 1",
    "Slap Bass 2",
    "Synth Bass 1",
    "Synth Bass 2",
    "Violin",
    "Viola",
    "Cello",
    "Contrabass",
    "Tremulo Strings",
    "Pizzicato String",
    "Orchestral Harp",
    "Timpany",
    "String Ensemble1",
    "String Ensemble2",
    "Synth Strings 1",
    "SynthStrings 2",
    "Choir Aahs",
    "Voice Oohs",
    "Synth Voice",
    "Orchestra Hit",
    "Trumpet",
    "Trombone",
    "Tuba",
    "Muted Trumpet",
    "French Horn",
    "Brass Section",
    "Synth Brass 1",
    "Synth Brass 2",
    "Soprano Sax",
    "Alto Sax",
    "Tenor Sax",
    "Baritone Sax",
    "Oboe",
    "English Horn",
    "Bassoon",
    "Clarinet",
    "Piccolo",
    "Flute",
    "Recorder",
    "Pan Flute",
    "Bottle Blow",
    "Shakuhachi",
    "Whistle",
    "Ocarina",
    "Lead 1 squareea",
    "Lead 2 sawtooth",
    "Lead 3 calliope",
    "Lead 4 chiff",
    "Lead 5 charang",
    "Lead 6 voice",
    "Lead 7 fifths",
    "Lead 8 brass",
    "Pad 1 new age",
    "Pad 2 warm",
    "Pad 3 polysynth",
    "Pad 4 choir",
    "Pad 5 bowedpad",
    "Pad 6 metallic",
    "Pad 7 halo",
    "Pad 8 sweep",
    "FX 1 rain",
    "FX 2 soundtrack",
    "FX 3 crystal",
    "FX 4 atmosphere",
    "FX 5 brightness",
    "FX 6 goblins",
    "FX 7 echoes",
    "FX 8 sci-fi",
    "Sitar",
    "Banjo",
    "Shamisen",
    "Koto",
    "Kalimba",
    "Bagpipe",
    "Fiddle",
    "Shanai",
    "Tinkle Bell",
    "Agogo Bells",
    "Steel Drums",
    "Woodblock",
    "Taiko Drum",
    "Melodic Tom",
    "Synth Drum",
    "Reverse Cymbal",
    "Guitar FretNoise",
    "Breath Noise",
    "Seashore",
    "Bird Tweet",
    "Telephone",
    "Helicopter",
    "Applause/Noise",
    "Gunshot",

    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>", // 27..34:  High Q; Slap; Scratch Push; Scratch Pull; Sticks;
    "<Reserved>", //          Square Click; Metronome Click; Metronome Bell
    "Ac Bass Drum",
    "Bass Drum 1",
    "Side Stick",
    "Acoustic Snare",
    "Hand Clap",
    "Electric Snare",
    "Low Floor Tom",
    "Closed High Hat",
    "High Floor Tom",
    "Pedal High Hat",
    "Low Tom",
    "Open High Hat",
    "Low-Mid Tom",
    "High-Mid Tom",
    "Crash Cymbal 1",
    "High Tom",
    "Ride Cymbal 1",
    "Chinese Cymbal",
    "Ride Bell",
    "Tambourine",
    "Splash Cymbal",
    "Cow Bell",
    "Crash Cymbal 2",
    "Vibraslap",
    "Ride Cymbal 2",
    "High Bongo",
    "Low Bongo",
    "Mute High Conga",
    "Open High Conga",
    "Low Conga",
    "High Timbale",
    "Low Timbale",
    "High Agogo",
    "Low Agogo",
    "Cabasa",
    "Maracas",
    "Short Whistle",
    "Long Whistle",
    "Short Guiro",
    "Long Guiro",
    "Claves",
    "High Wood Block",
    "Low Wood Block",
    "Mute Cuica",
    "Open Cuica",
    "Mute Triangle",
    "Open Triangle",
    "Shaker",
    "Jingle Bell",
    "Bell Tree",
    "Castanets",
    "Mute Surdu",
    "Open Surdu",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>",
    "<Reserved>"
};


const char *get_instrument_name(unsigned bank, unsigned patch)
{
    if(bank == 0)
        return gm_names[patch];
    if(bank == 127)
        return gm_names[patch + 128];
    return "<unknown>";
}

int endsWith(const char *str, const char *suffix)
{
    size_t lenstr;
    size_t lensuffix;

    if(!str || !suffix)
        return 0;

    lenstr = strlen(str);
    lensuffix = strlen(suffix);

    if(lensuffix >  lenstr)
        return 0;

    return stricmp(str + lenstr - lensuffix, suffix) == 0;
}


/***************************************************************/

//
// Standard C routine for Global Timbre Library access
//

void *load_global_timbre(FILE *GTL, unsigned short bank, unsigned short patch)
{
    unsigned short *timb_ptr;
    static unsigned short len;
    int loops = 0;

#pragma pack (push, 1)
    static struct                 // GTL file header entry structure
    {
        signed char patch;
        signed char bank;
        uint32_t offset;
    }
    GTL_hdr;
#pragma pack (pop)

    if(GTL == NULL)
    {
        printf("GTL is NULL\n");
        return NULL;   // if no GTL, return failure
    }

    fseek(GTL, 0, SEEK_SET);                   // else rewind to GTL header

    do                             // search file for requested timbre
    {
        fread(&GTL_hdr, sizeof(GTL_hdr), 1, GTL);

        printf("%d, %d [size=%u]\n", GTL_hdr.bank, GTL_hdr.patch, sizeof(GTL_hdr));

        if(GTL_hdr.bank == -1)
        {
            printf("Timbre not found %u %u on loop %d\n", bank, patch, loops);
            return NULL;             // timbre not found, return NULL
        }
        loops++;
    }
    while((GTL_hdr.bank != bank) ||
          (GTL_hdr.patch != patch));

    fseek(GTL, GTL_hdr.offset, SEEK_SET);
    fread(&len, 2, 1, GTL);        // timbre found, read its length

    timb_ptr = malloc(len);        // allocate memory for timbre ..
    *timb_ptr = len;
    // and load it
    fread((timb_ptr + 1), len - 2, 1, GTL);

    if(ferror(GTL))                // return NULL if any errors
        return NULL;                // occurred
    else
        return timb_ptr;            // else return pointer to timbre
}

/***************************************************************/
void main(int argc, char *argv[])
{
    HDRIVER hdriver;
    HSEQUENCE hseq;
    drvr_desc *desc;
    FILE *GTL;
    char GTL_filename[32];
    char *state;
    char *drvr, *dll;
    char *timb;
    char *tc_addr;
    unsigned char *buffer;
    unsigned long state_size;
    unsigned short bank, patch, tc_size, seqnum;
    unsigned short treq;

    char key;
    const char *drPath = "a32sp2fm.dll";
    const char *gtlPath = NULL;
    const char *xmiPath = NULL;
    const char *xmiPathOrig = NULL;
    int keepWork = 0;
    int i;

    setbuf(stdout, NULL);

    for(i = 1; i < argc;)
    {
        if(!strcmp(argv[i], "-d"))
        {
            if(i == argc - 1)
            {
                printf("Missing driver filename after -d argument!\n");
                exit(1);
            }
            drPath = argv[i + 1];
            i += 2;
            continue;
        }
        else if(!strcmp(argv[i], "-g"))
        {
            if(i == argc - 1)
            {
                printf("Missing global timbre library filename after -g argument!\n");
                exit(1);
            }
            gtlPath = argv[i + 1];
            i += 2;
            continue;
        }

        break;
    }

    if(i < argc)
        xmiPath = argv[i];
    i++;

    seqnum = 0;
    if(i < argc)
        seqnum = atoi(argv[i]);


    printf("\nXP32 version %s                   Copyright (C) 1991, 1992 Miles Design, Inc.\n", VERSION);
    printf("-------------------------------------------------------------------------------\n\n");

    if(argc < 2 || !xmiPath)
    {
        printf("This program plays an Extended MIDI (XMIDI) sequence through a \n");
        printf("specified AIL/32 sound driver.\n\n");
        printf("Usage: XP32 [-d driver_filename] [-g timbre_file_name] XMIDI_filename [sequence_number]\n");
        exit(1);
    }

    //
    // Load driver file
    //

    dll = FILE_read((char *)drPath, NULL);
    if(dll == NULL)
    {
        printf("Could not load driver '%s'.\n", drPath);
        exit(1);
    }

    drvr = DLL_load(dll, DLLMEM_ALLOC | DLLSRC_MEM, NULL);
    if(drvr == NULL)
    {
        printf("Invalid DLL image.\n");
        exit(1);
    }

    free(dll);

    //
    // Initialize API before calling any Library functions
    //

    AIL_startup();

    //
    // Register the driver with the API
    //

    hdriver = AIL_register_driver(drvr);
    if(hdriver == -1)
    {
        printf("Driver %s not compatible with linked API version.\n",
               drPath);
        AIL_shutdown(NULL);
        exit(1);
    }

    //
    // Get driver type and factory default I/O parameters; exit if
    // driver is not capable of interpreting MIDI files
    //

    desc = AIL_describe_driver(hdriver);

    if(desc->drvr_type != XMIDI_DRVR)
    {
        printf("Driver %s not an XMIDI driver.\n", drPath);
        AIL_shutdown(NULL);
        exit(1);
    }

    //
    // Verify presence of driver's sound hardware and prepare
    // driver/hardware for use
    //

    if(!AIL_detect_device(hdriver, desc->default_IO, desc->default_IRQ,
                          desc->default_DMA, desc->default_DRQ))
    {
        printf("Sound hardware not found.\n");
        AIL_shutdown(NULL);
        exit(1);
    }


    AIL_init_driver(hdriver, desc->default_IO, desc->default_IRQ,
                    desc->default_DMA, desc->default_DRQ);

    state_size = AIL_state_table_size(hdriver);

    //
    // Load XMIDI data file
    //

    buffer = FILE_read((char *)xmiPath, NULL);
    if(buffer == NULL)
    {
        printf("Can't load XMIDI file %s.\n", xmiPath);
        AIL_shutdown(NULL);
        exit(1);
    }

    //
    // Get name of Global Timbre Library file by appending suffix
    // supplied by XMIDI driver to GTL filename prefix "SAMPLE."
    //

    if(!gtlPath)
    {
        strcpy(GTL_filename, "fat.");
        strcat(GTL_filename, desc->data_suffix);
    }
    else
        strcpy(GTL_filename, gtlPath);

    //
    // Set up local timbre cache; open Global Timbre Library file
    //

    tc_size = AIL_default_timbre_cache_size(hdriver);

    if(tc_size)
    {
        tc_addr = malloc((unsigned long) tc_size);
        AIL_define_timbre_cache(hdriver, tc_addr, tc_size);
    }

    GTL = fopen(GTL_filename, "rb");

    printf("Opening of GTL: %s\n", GTL_filename);

    //
    // Look up and register desired sequence in XMIDI file, loading
    // timbres if needed
    //

    state = malloc(state_size);
    if((hseq = AIL_register_sequence(hdriver, buffer, seqnum, state,
                                     NULL)) == -1)
    {
        printf("Sequence %u not present in XMIDI file \"%s\".\n",
               seqnum, xmiPath);
        AIL_shutdown(NULL);
        exit(1);
    }

    while((treq = AIL_timbre_request(hdriver, hseq)) != 0xffff)
    {
        bank = treq / 256;
        patch = treq % 256;

        timb = load_global_timbre(GTL, bank, patch);

        if(timb != NULL)
        {
            AIL_install_timbre(hdriver, bank, patch, timb);
            free(timb);
            printf("Installed timbre bank %u, patch %u (%s)\n", bank, patch, get_instrument_name(bank, patch));
        }
        else
        {
            printf("Timbre bank %u, patch %u not found ", bank, patch);
            printf("in Global Timbre Library %s\n", GTL_filename);
            AIL_shutdown(NULL);
            exit(1);
        }
    }

    if(GTL != NULL) fclose(GTL);

    //
    // Start music playback
    //

    printf("Playing sequence %u from XMIDI file \"%s\" ...\n\n",
           seqnum, xmiPath);

    AIL_start_sequence(hdriver, hseq);

#ifdef __HIGHC__

    printf("Press any key to stop ... \n");

    while(AIL_sequence_status(hdriver, hseq) != SEQ_DONE)
    {
        if(kbhit())
        {
            getch();
            break;
        }
    }

#else
    printf("----------------------\n");
    if(xmiPathOrig)
        printf("Song: %s (sequence %d)\n", xmiPathOrig, seqnum);
    else
        printf("Song: %s (sequence %d)\n", xmiPath, seqnum);
    printf("Timbre bank: %s\n", GTL_filename);
    printf("Driver: %s\n", drPath);
    printf("----------------------\n");
    printf("Press ESC to stop the song.\n");
    printf("----------------------\n");
    printf("S - Pause/Stop song\n");
    printf("R - Resume paused song\n");
    printf("P - Play song at start\n");
    printf("----------------------\n");
    // spawnlp(P_WAIT, "pause", NULL);

    keepWork = 1;
    while(keepWork)
    {
        key = getch();
        switch(key)
        {
        case 'r':
        case 'R':
            AIL_resume_sequence(hdriver, hseq);
            break;
        case 's':
        case 'S':
            AIL_stop_sequence(hdriver, hseq);
            break;
        case 'p':
        case 'P':
            AIL_start_sequence(hdriver, hseq);
            break;
        case 27:
            keepWork = 0;
            break;
        }
    }
#endif

    //
    // Shut down API and all installed drivers; write XMIDI filename
    // to any front-panel displays
    //

    printf("XP32 stopped.\n");

    AIL_shutdown((char *)xmiPath);
}


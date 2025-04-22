#ifndef _VAD_H
#define _VAD_H
#include <stdio.h>

/* TODO: add the needed states */
typedef enum {
   ST_UNDEF=0, 
   ST_SILENCE, 
   ST_VOICE, 
   ST_INIT,
   ST_MAYBE_SILENCE,
   ST_MAYBE_VOICE
   } VAD_STATE;

/* Return a string label associated to each state */
const char *state2str(VAD_STATE st);

/* TODO: add the variables needed to control the VAD 
   (counts, thresholds, etc.) */
typedef struct {
  VAD_STATE state;
  int first_silence;
  float sampling_rate;
  unsigned int frame_length;
  float last_feature; /* for debuggin purposes */
  float p0, const1, const2,alpha0, alpha1, alpha2;
  float zcr_stv, zcr_vts;
  int maybe_v_counter, maybe_s_counter, init_counter;
  int counter;
  int min_voice, min_silence;
} VAD_DATA;

/* Call this function before using VAD: 
   It should return allocated and initialized values of vad_data

   sampling_rate: ... the sampling rate */
VAD_DATA *vad_open(float rate, float alpha1, float alpha2, int min_silence, int min_voice, float zcr_stv, float zcr_vts, int init_counter);

/* vad works frame by frame.
   This function returns the frame size so that the program knows how
   many samples have to be provided */
unsigned int vad_frame_size(VAD_DATA *);

/* Main function. For each 'time', compute the new state 
   It returns:
    ST_UNDEF   (0) : undefined; it needs more frames to take decission
    ST_SILENCE (1) : silence
    ST_VOICE   (2) : voice

    x: input frame
       It is assumed the length is frame_length */
VAD_STATE vad(VAD_DATA *vad_data, float *x);

/* Free memory
   Returns the state of the last (undecided) states. */
VAD_STATE vad_close(VAD_DATA *vad_data);

/* Print actual state of vad, for debug purposes */
void vad_show_state(const VAD_DATA *, FILE *);

#endif
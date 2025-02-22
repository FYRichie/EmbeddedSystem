/*
 * Copyright (C) 2018 Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Description: Example code for running keyword spotting on Cortex-M boards
 */

// #include "md_simple.h"

#include "stdio.h"
#include "mbed.h"
#include "motion_detect.h"

#include "WAVEDATA.h"

// #include "wav_data.h"

// int16_t audio_buffer[16000]=WAVE_DATA;

// q15_t motiondata_buffer[24] = {0,1,2,3,4,5,6,4,8,9,0,1,2,3,4,5,6,4,8,9,0,1,2,3};

// int16_t motiondata_buffer[24] = {0,1,2,3,4,5,6,4,8,9,0,1,2,3,4,5,6,4,8,9,0,1,2,3};

// left
// int16_t motiondata_buffer[24] = {264, -87, 467, 24, -177, 362, -32, -359, 291, -82, -99, 174, 70, -111, 346, -11, -156, 328, -40, -203, 385, 81, -355, 450};



// right
int16_t motiondata_buffer[24] = {-81, 21, 128, 2, 149, 179, 53, -34, 73, -269, 69, 254, 191, -26, 82, -75, 119, 208, 34, 10, 101, 29, 148, 52};



int16_t left_wavadata[24*LEFT_WAVEDATA_NUMBER] = LEFT_WAVEDATA;

// Timer T;
// //Serial pc(USBTX, USBRX);

// int main()
// {
//   printf("HAHA!");
//   // char output_class[12][8] = {"Silence", "Unknown","yes","no","up","down","left","right","on","off","stop","go"};
//   char output_class[4][8] = {"left","right","stop","none"};
  
//   MOTION_DETECT motiondetect(motiondata_buffer);

//   T.start();
//   int start=T.read_us();

//   motiondetect.classify();	  //classify using dnn
//   int end=T.read_us();
//   T.stop();
//   int max_ind = motiondetect.get_top_class(motiondetect.output);
//   //pc.printf("Total time : %d us\r\n",end-start);
//   printf("Detected %s (%d%%)\r\n",output_class[max_ind],((int)motiondetect.output[max_ind]*100/128));

//   return 0;
// }



// void predict(MOTION_DETECT *motiondetect)
// {
//   motiondetect.classify();	  //classify using dnn

//   int max_ind = motiondetect.get_top_class(motiondetect.output);
//   printf("Detected %s (%d%%)\r\n",output_class[max_ind],((int)motiondetect.output[max_ind]*100/128));

// }


void update_motiondata_buffer(int dataindex, int16_t *wavadata)
{ // dataindex = 0, 1, 2, 3 ...
  for (int i = 0; i < 24; i++){
    motiondata_buffer[i] = wavadata[24*dataindex+i];
  }
  return;
}


int main()
{
  
  char output_class[4][8] = {"left","right","stop","none"};
  
  MOTION_DETECT motiondetect(motiondata_buffer);



  printf("start test !\n");
  for (int dataindex = 0; dataindex < LEFT_WAVEDATA_NUMBER; dataindex++){
    update_motiondata_buffer(dataindex, left_wavadata);
    
    motiondetect.classify();	  //classify using dnn

    int max_ind = motiondetect.get_top_class(motiondetect.output);
    printf("Detected %s (%d%%)\r\n",output_class[max_ind],((int)motiondetect.output[max_ind]*100/128));

  }

  printf("end test !\n\n");
  

  return 0;
}

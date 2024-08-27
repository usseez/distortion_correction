#pragma once
#ifndef DISTORTIONCORRECTION_H //headerÀÌ¸§_H
#define DISTORTIONCORRECTION_H
#define IMAGEWIDTH 640
#define IMAGEHEIGHT 480
#define CHANNEL 3

#ifdef __cplusplus 
		extern"C" {
#endif

	extern void distortion_correction(unsigned char* inputimage, unsigned char* outimage);
    
#ifdef __cplusplus

		} /*end of the 'externC' block*/
#endif

#endif	// 
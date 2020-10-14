#include <stdio.h>
#include <stdlib.h>
#include "mml.h"

char track[] = "t180r2>c8c32r64d16d64e8.e32.r4r64d8d32r64c16c64g8.g32.r4r64e8e32r64g16g64>c8.c32.r64<b8.b32.r64a8a32r64g16g64e8.e32.r4r64d8.d32.r64c8.c32.r4r64e8.e32.r64<g+8.g+32.r64a8.a32.r64b8.b32.r64>c2c8.c32r32d4.d16.r32c8c32.r64d16e4.e16.r32d8d32r64c16c64g4.g16.r32e8e32r64g16g64>c8.c32.r64<b8.b32.r64>c8c32r64d16d64g8.g32.r64d8d32r64c16c64<g8g32.r64a+16g4.g16.r32f8f32r64d+16d+64d8.d32.r64d+8.d+32.r64f8.f32.r4r64f4r4f4r4f8.f32.r4r64d+4r4d+4r4d+8.d+32.r4r64d+4r4d+4r4d+8.d+32.r4r64f4.f16.r32f4.f16.r32g8.g32.r64<f16r8.f16r8.f16r8.f16r8.f16r8.f16r8.g16r8.g16r8.g16r8.g+16r8.g+16r8.g+16r8.a+16r8.f16r16>d+16r16c+16r16c16r16<a+16r8.>c16r8.<g+16r8.a+16r8.>c16r8.<f16r8.f16r8.f16r8.f16r8.f16r8.>c16r8.<f16r8.>d+16r8.c+16r8.c16r8.<d+16r8.a+16r8.d+16r8.>c+16r8.<b16r16a+16r16g+16r16f+16r16f16r8.f+16r8.g+16r16a+16r16f16r8.<a+16r8.>c+16r8.d+16r8.d+16r8.d+16r8.d+16r8.d+16r8.d+16r8.<a+2a+8.a+32r32a2a8.a32r4r32a+8.a+32.r64>c8.c32.r64f8.f32.r64c4.c16.r2.r32<f4.f16.r32>c8.c32.r64<a2a8.a32r32a2a8.a32r32>c2c8.c32r32d2d8.d32r4r32f8.f32.r64g8.g32.r64>c8.c32.r64<a4.a16.r32e2e8.e32r32f+4.f+16.r32f8e8d+4.r4.d+2d+8.d+32r32>b2b8.b32r32>c+4.c+16r4r16>d+16c+16<b16g+16d+16c+16<b16g+16r4d+4.d+16r4r16g+2g+8.g+32r32>f+8.f+32.r64g+8.g+32.r64f+16g+16a+16>d+16<g+16f+16g+16f+16g+16f+16g+16f+16g+16c+16d+16c+16<g+16a+16>c16<d+4d+16d+8.d+32r32f+4.f+16.r32g+8a+8g+8.g+32.r64c+8.c+32.r64f8.f32.r64g+8.g+32.r64>c+8.c+32.r64<b8.b32.r64a+8.a+32.r64g8.g32.r64g+8.g+32.r64a+8.a+32.r64f+8.f+32.r64d+8c+8d+8.d+32.r64f+8.f+32.r64b8.b32.r64a+4.a+16.r32d+8c+8d+4d+16.d+64r64<a+8b8>c+8d+4r8<<g32r64a+32>d+32.a+32r64<d+32g32.a+32r64>d+32g32.>d+32r64<<a+32>g32.a+32r64>d+32<a+32.>g32r64<g32a+32.>d+32r64a+32>d+32.<<g32r64>d+32>d+32.g32r64a+32>d+32.g32e64r64d64<b32g32f64r64d64<b32g32>g32e64r64d64<b32g32f64r64d64<b32g32>g32e64r64d64<b32a32g64r64f64d32<b32>g32f32r64d32<b32g32f32.<g32r2o6e4.e16.r32d8d32r64c16c64g4.g16.r32e8e32r64g16g64>c8.c32.r64<b8.b32.r64a8a32r64g16g64e4.e16.r32d8.d32.r64c4.c16.r32e8.e32.r64<g+8.g+32.r64a8.a32.r64b8.b32.r64>c2c8.c32r32>c2c8.c32r4r32<<f8.f32.r64c+8.c+32.r64c8.c32.r64g+8.g+32.r64d+8.d+32.r64g+8.g+32.r64a8.a32.r64a+8.a+32.r64d+8.d+32.r64c+8.c+32.r64c8.c32.r64<a+8.a+32.r64>f8.f32.r64c+8.c+32.r64c8.c32.r64d+8.d+32.r64c+8.c+32.r64c4.c16.r32<a+8.a+32.r64a1a4.a32.r16r64>c8.c32.r64c+8.c+32.r64d+8.d+32.r64<f4.f16.r32d+8c+8g+4.g+16.r32f8g+8>c+8.c+32.r64c8.c32.r64<g+8.g+32.r64f4.f16.r32d+8.d+32.r64c+4.c+16.r32f8.f32.r64<a8.a32.r64a+8.a+32.r64>c8.c32.r64g2g8.g32r32a2a8.a32r32f4.f16.r32d+8c+8g+4.g+16.r32f8g+8>c+4c+16.c+64r64c4c16.c64r64<g+4g+16.g+64r64d+4d+16.d+64r64c+4.c+16.r32f8.f32.r64>c8.c32.r64c+8.c+32.r64d+8.d+32.r64g+16f+16f16d+16c+16c16<a+16g+16f+16f16d+16c+16c16c+16d+16f16f+16g+16a+16>c16c+16d+16f16g+16a+16g+16f+16f16d+16c+16c16<a+16g+16f+16f16d+16c16c+16d+16f16g16a16a+16>c16c+16d+16f16f+16g+16f+16f16d+16c+16c16<a+16g+16f+16f16d+16c+16c16c+16d+16f16f+16a16a+16>c16c+16d+16f16f+16a+16g+16f+16f16d+16c+16c16<a+16g+16f+16f16d+16c16c+16d+16f16f+16a16a+16>c16c+16d+16f16f+16g+16f+16f16d+16c+16c16<a+16g+16f+16f16d+16c+16c16c+16d+16f16f+16g+16a+16>c16c+16d+16f16g+16c+4c+16.c+64r64c4c16.c64r64c+4c+16.c+64r64d+4d+16.d+64r64<g+16>f+16f16d+16c+16c16<a+16g+16f+16f16d+16c+16c16c+16d+16f16f+16g+16a+16>c16c+16d+16f16f+16t178a16f+16f16d+16t176c+16c16<a16f+16t173f16d+16c+16c16t172c16c+16d+16f16t169f+16a16a+16>c16t167c+16d+16f16f+16t166f4.f16.r32d+8d+32r64c+16c+64g+4.g+16.r32f8f32r64g+16g+64>c+8.c+32.r64c8.c32.r64<a+8a+32r64g+16g+64f4.f16.r32d+8.d+32.r64c+4.c+16.r32f8.f32.r64c8.c32.r64c+8.c+32.r64c8.c32.r64c2c8.c32r32<a+4.a+16.r32>>c+8c+32r64d+16d+64<a+4.a+16.r32>d+8d+32r64c+16c+64c8.c32.r64<g+8.g+32.r64d+8.d+32.r64g+8.g+32.r64a8.a32.r64a+8.a+32.r64d+8.d+32.r64c+8.c+32.r64>c+8c+32r64d+16d+64<g+4.g+16.r32>d+8d+32r64c+16c+64<g+2g+8.g+32r2.r32f8.f32.r64>c+8.c+32.r64d+8.d+32.r64>c1c4.c16.r32o3g+16c+16f16g+16>c+16<f16g+16>c+16f16<g+16>c+16f16g+16c+16f16g+16>c+16<f16g+16>c+16f16<g+16>c+16f16g+16c+16f16g+16>c+16<f16g+16>c+16f16<g+16>c+16f16g+16c+16f16g+16>c+16<f16g+16>c+16f16<g+16>c+16f16g+1g+4.g+32.";
FILE *stream;

static void mml_callback(MML_INFO *p, void *extobj);

int main(void){
	MML mml;
	MML_OPTION mml_opt;
	MML_RESULT mml_res;
	
	stream = fopen("mml_parsed.txt", "w");
	if(stream == NULL){
		fprintf(stderr, "file open error\n");
		exit(EXIT_FAILURE);
	}
	
	mml_init(&mml, mml_callback, NULL);
	MML_OPTION_INITIALIZER_DEFAULT(&mml_opt);
	
	mml_setup(&mml, &mml_opt, track);
	while((mml_res = mml_fetch(&mml)) == MML_RESULT_OK);
	
	printf("exit: %d\n", mml_res);
	
	system("pause");
	fclose(stream);
	return 0;
}

static void mml_callback(MML_INFO *p, void *extobj){
	switch(p->type){
	case MML_TYPE_NOTE:{
		MML_ARGS_NOTE *args = &(p->args.note);
		fprintf(stream, "[NOTE  : Number=%3d, Ticks=%4d]\n", args->number, args->ticks);
		}
		break;	
	case MML_TYPE_REST:{
		MML_ARGS_REST *args = &(p->args.rest);
		fprintf(stream, "[REST  :             Ticks=%4d]\n", args->ticks);
		}
		break;
	case MML_TYPE_TEMPO:{
		MML_ARGS_TEMPO *args = &(p->args.tempo);
		fprintf(stream, "[TEMPO : Value=%3d]\n", args->value);	
		}
		break;
	default:
		break;
	}
}


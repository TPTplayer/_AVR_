#include <stdio.h>
#include <stdlib.h>
#include "mml.h"

char track[] = ""; /*MML string*/

static void mml_callback(MML_INFO *p, void *extobj);

int main(void){
	MML mml;
	MML_OPTION mml_opt;
	
	mml_init(&mml, mml_callback, NULL);
	MML_OPTION_INITIALIZER_DEFAULT(&mml_opt);
	
	mml_setup(&mml, &mml_opt, track);
	while(mml_fetch(&mml) == MML_RESULT_OK);
	
	system("pause");
	return 0;
}

static void mml_callback(MML_INFO *p, void *extobj){
	switch(p->type){
	case MML_TYPE_NOTE:{
		MML_ARGS_NOTE *args = &(p->args.note);
		printf("[NOTE  : Number=%3d, Ticks=%4d]\n", args->number, args->ticks);
		}
		break;	
	case MML_TYPE_REST:{
		MML_ARGS_REST *args = &(p->args.rest);
		printf("[REST  :             Ticks=%4d]\n", args->ticks);
		}
		break;
	case MML_TYPE_TEMPO:{
		MML_ARGS_TEMPO *args = &(p->args.tempo);
		printf("[TEMPO : Value=%3d]\n", args->value);	
		}
		break;
	default:
		break;
	}
}


/*
 * Brickworks
 *
 * Copyright (C) 2022 Orastron Srl unipersonale
 *
 * Brickworks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Brickworks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *
 * File authors: Stefano D'Angelo
 */

#include "config.h"
#include "walloc.h"

struct _wrapper {
	P_TYPE		 instance;
	// wasting a little bit of memory if buses are mono, but let's KISS
#if NUM_BUSES_IN != 0
	float		 ins[NUM_BUSES_IN * 2 * 128];
	const float	*x[NUM_BUSES_IN * 2];
#endif
#if NUM_BUSES_OUT != 0
	float		 outs[NUM_BUSES_OUT * 2 * 128];
	float		*y[NUM_BUSES_OUT * 2];
#endif
#if NUM_PARAMETERS != 0
	float		 param_values[NUM_PARAMETERS];
#endif
};

typedef struct _wrapper *wrapper;

void wrapper_set_parameter(wrapper w, int index, float value);

wrapper wrapper_new(float sample_rate) {
	wrapper ret = malloc(sizeof(struct _wrapper));
	if (ret == NULL)
		return NULL;

	ret->instance = P_NEW();
	if (ret->instance == NULL) {
		free(ret);
		return NULL;
	}

#if NUM_BUSES_IN != 0
	int dx = 0;
	for (int i = 0; i < NUM_BUSES_IN; i++) {
		ret->x[i] = ret->ins + dx;
		dx += 128;
		if (config_buses_in[i].configs & IO_STEREO) {
			ret->x[i] = ret->ins + dx;
			dx += 128;
		}
	}
#endif
#if NUM_BUSES_OUT != 0
	int dy = 0;
	for (int i = 0; i < NUM_BUSES_OUT; i++) {
		ret->y[i] = ret->outs + dy;
		dy += 128;
		if (config_buses_out[i].configs & IO_STEREO) {
			ret->y[i] = ret->outs + dy;
			dy += 128;
		}
	}
#endif

#if NUM_PARAMETERS != 0
	for (int i = 0; i < NUM_PARAMETERS; i++)
		wrapper_set_parameter(ret, i, config_parameters[i].defaultValueUnmapped);
#endif

	P_SET_SAMPLE_RATE(ret->instance, sample_rate);
	P_RESET(ret->instance);

	return ret;
}

void wrapper_free(wrapper w) {
	P_FREE(w->instance);
	free(w);
}

float *wrapper_get_ins(wrapper w) {
#if NUM_BUSES_IN != 0
	return w->ins;
#else
	return NULL;
#endif
}

float *wrapper_get_outs(wrapper w) {
#if NUM_BUSES_OUT != 0
	return w->outs;
#else
	return NULL;
#endif
}

float *wrapper_get_param_values(wrapper w) {
#if NUM_PARAMETERS != 0
	return w->param_values;
#else
	return NULL;
#endif
}

void wrapper_process(wrapper w, int n_samples) {
#if NUM_BUSES_IN != 0
	const float **x = w->x;
#else
	const float **x = NULL;
#endif
#if NUM_BUSES_OUT != 0
	float **y = w->y;
#else
	float **y = NULL;
#endif
	P_PROCESS(w->instance, x, y, n_samples);

#if NUM_PARAMETERS != 0
	for (int i = 0; i < NUM_PARAMETERS; i++)
		w->param_values[i] = P_GET_PARAMETER(w->instance, i);
#endif
}

void wrapper_set_parameter(wrapper w, int index, float value) {
#if NUM_PARAMETERS != 0
	P_SET_PARAMETER(w->instance, index, value);
	w->param_values[index] = value;
#endif
}

void wrapper_note_on(wrapper w, int note, int velocity) {
#ifdef P_NOTE_ON
	P_NOTE_ON(w->instance, note, velocity);
#endif
}

void wrapper_note_off(wrapper w, int note) {
#ifdef P_NOTE_OFF
	P_NOTE_OFF(w->instance, note);
#endif
}

/*
	Audio File Library
	Copyright (C) 1998-2000, Michael Pruett <michael@68k.org>

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the
	Free Software Foundation, Inc., 59 Temple Place - Suite 330,
	Boston, MA  02111-1307  USA.
*/

/*
	AIFF.h

	This file contains structures and constants related to the AIFF
	and AIFF-C formats.
*/

#ifndef AIFF_H
#define AIFF_H

#include "File.h"
#include "afinternal.h"
#include "audiofile.h"
#include <stdint.h>

#define AIFC_VERSION_1 0xa2805140

struct _INST
{
	uint8_t		baseNote;
	int8_t		detune;
	uint8_t		lowNote, highNote;
	uint8_t		lowVelocity, highVelocity;
	int16_t		gain;

	uint16_t	sustainLoopPlayMode;
	uint16_t	sustainLoopBegin;
	uint16_t	sustainLoopEnd;

	uint16_t	releaseLoopPlayMode;
	uint16_t	releaseLoopBegin;
	uint16_t	releaseLoopEnd;
};

#define _AF_AIFF_NUM_INSTPARAMS 9
extern const InstParamInfo _af_aiff_inst_params[_AF_AIFF_NUM_INSTPARAMS];
#define _AF_AIFFC_NUM_COMPTYPES 2
extern const int _af_aiffc_compression_types[_AF_AIFFC_NUM_COMPTYPES];

class AIFFFile : public _AFfilehandle
{
public:
	AIFFFile();

	static bool recognizeAIFF(File *fh);
	static bool recognizeAIFFC(File *fh);

	static AFfilesetup completeSetup(AFfilesetup);

	virtual int getVersion();

	virtual status readInit(AFfilesetup);
	virtual status writeInit(AFfilesetup);

	virtual status update();

	virtual bool isInstrumentParameterValid(AUpvlist, int);

private:
	AFfileoffset	miscellaneousPosition;
	AFfileoffset	FVER_offset;
	AFfileoffset	COMM_offset;
	AFfileoffset	MARK_offset;
	AFfileoffset	INST_offset;
	AFfileoffset	AESD_offset;
	AFfileoffset	SSND_offset;

	status parseFVER(uint32_t type, size_t size);
	status parseAESD(uint32_t type, size_t size);
	status parseMiscellaneous(uint32_t type, size_t size);
	status parseINST(uint32_t type, size_t size);
	status parseMARK(uint32_t type, size_t size);
	status parseCOMM(uint32_t type, size_t size);
	status parseSSND(uint32_t type, size_t size);

	status writeCOMM();
	status writeSSND();
	status writeMARK();
	status writeINST();
	status writeFVER();
	status writeAESD();
	status writeMiscellaneous();
};

#endif
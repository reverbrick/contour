//----------------------------------------------------------
// name: "GreyholeRaw"
// version: "1.0"
// author: "Julian Parker, bug fixes by Till Bovermann"
// license: "GPL2+"
// copyright: "(c) Julian Parker 2013"
//
// Code generated with Faust 0.9.95 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2006-2011 Albert Graef <Dr.Graef@t-online.de>
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as 
	published by the Free Software Foundation; either version 2.1 of the 
	License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
 	License along with the GNU C Library; if not, write to the Free
  	Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  	02111-1307 USA. 
 ************************************************************************
 ************************************************************************/

/* Pd architecture file, written by Albert Graef <Dr.Graef@t-online.de>.
   This was derived from minimal.cpp included in the Faust distribution.
   Please note that this is to be compiled as a shared library, which is
   then loaded dynamically by Pd as an external. */

#include <stdlib.h>
#include <math.h>
#include <string>

/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <string.h>
#include <stdlib.h>

/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif

using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

inline int lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }

inline int int2pow2(int x)		{ int r = 0; while ((1<<r) < x) r++; return r; }

inline long lopt(char* argv[], const char* name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

inline bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

inline const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    protected:
    
        UI* fUI;

    public:
    
        DecoratorUI(UI* ui = 0):fUI(ui)
        {}

        virtual ~DecoratorUI() { delete fUI; }

        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
            { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
            { fUI->addNumEntry(label, zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
            { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            { fUI->addVerticalBargraph(label, zone, min, max); }

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }

};

#endif
/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the UI* parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the UI* user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /** Global init, calls the following methods :
         * - static class 'classInit' : static table initialisation
         * - 'instanceInit' : constants and instance table initialisation
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void init(int samplingRate) = 0;
    
        /** Init instance state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceInit(int samplingRate) = 0;
    
        /** Init instance constant state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceConstants(int samplingRate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
    
        /**  
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value metadata).
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with sucessive in/out audio buffers.
         *
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation : alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int samplingRate) { fDSP->init(samplingRate); }
        virtual void instanceInit(int samplingRate) { fDSP->instanceInit(samplingRate); }
        virtual void instanceConstants(int samplingRate) { fDSP->instanceConstants(samplingRate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { return fDSP->metadata(m); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
       
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/***************************************************************************
   Pd UI interface
 ***************************************************************************/

enum ui_elem_type_t {
  UI_BUTTON, UI_CHECK_BUTTON,
  UI_V_SLIDER, UI_H_SLIDER, UI_NUM_ENTRY,
  UI_V_BARGRAPH, UI_H_BARGRAPH,
  UI_END_GROUP, UI_V_GROUP, UI_H_GROUP, UI_T_GROUP
};

struct ui_elem_t {
  ui_elem_type_t type;
  char *label;
  float *zone;
  float init, min, max, step;
};

class PdUI : public UI
{
public:
  const char *name;
  int nelems, level;
  ui_elem_t *elems;
		
  PdUI();
  PdUI(const char *nm, const char *s);
  virtual ~PdUI();

protected:
  std::string path;
  void add_elem(ui_elem_type_t type, const char *label = NULL);
  void add_elem(ui_elem_type_t type, const char *label, float *zone);
  void add_elem(ui_elem_type_t type, const char *label, float *zone,
		float init, float min, float max, float step);
  void add_elem(ui_elem_type_t type, const char *label, float *zone,
		float min, float max);

public:
  virtual void addButton(const char* label, float* zone);
  virtual void addCheckButton(const char* label, float* zone);
  virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
  virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
  virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);

  virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
  virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);
  
  virtual void openTabBox(const char* label);
  virtual void openHorizontalBox(const char* label);
  virtual void openVerticalBox(const char* label);
  virtual void closeBox();
	
  virtual void run();
};

static std::string mangle(const char *name, int level, const char *s)
{
  const char *s0 = s;
  std::string t = "";
  if (!s) return t;
  // Get rid of bogus "0x00" labels in recent Faust revisions. Also, for
  // backward compatibility with old Faust versions, make sure that default
  // toplevel groups and explicit toplevel groups with an empty label are
  // treated alike (these both return "0x00" labels in the latest Faust, but
  // would be treated inconsistently in earlier versions).
  if (!*s || strcmp(s, "0x00") == 0) {
    if (level == 0)
      // toplevel group with empty label, map to dsp name
      s = name;
    else
      // empty label
      s = "";
  }
  while (*s)
    if (isalnum(*s))
      t += *(s++);
    else {
      const char *s1 = s;
      while (*s && !isalnum(*s)) ++s;
      if (s1 != s0 && *s) t += "-";
    }
  return t;
}

static std::string normpath(std::string path)
{
  path = std::string("/")+path;
  int pos = path.find("//");
  while (pos >= 0) {
    path.erase(pos, 1);
    pos = path.find("//");
  }
  size_t len = path.length();
  if (len > 1 && path[len-1] == '/')
    path.erase(len-1, 1);
  return path;
}

static std::string pathcat(std::string path, std::string label)
{
  if (path.empty())
    return normpath(label);
  else if (label.empty())
    return normpath(path);
  else
    return normpath(path+"/"+label);
}

PdUI::PdUI()
{
  nelems = level = 0;
  elems = NULL;
  name = "";
  path = "";
}

PdUI::PdUI(const char *nm, const char *s)
{
  nelems = level = 0;
  elems = NULL;
  name = nm?nm:"";
  path = s?s:"";
}

PdUI::~PdUI()
{
  if (elems) {
    for (int i = 0; i < nelems; i++)
      if (elems[i].label)
	free(elems[i].label);
    free(elems);
  }
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  std::string s = pathcat(path, mangle(name, level, label));
  elems[nelems].type = type;
  elems[nelems].label = strdup(s.c_str());
  elems[nelems].zone = NULL;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 0.0;
  elems[nelems].step = 0.0;
  nelems++;
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label, float *zone)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  std::string s = pathcat(path, mangle(name, level, label));
  elems[nelems].type = type;
  elems[nelems].label = strdup(s.c_str());
  elems[nelems].zone = zone;
  elems[nelems].init = 0.0;
  elems[nelems].min = 0.0;
  elems[nelems].max = 1.0;
  elems[nelems].step = 1.0;
  nelems++;
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label, float *zone,
			  float init, float min, float max, float step)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  std::string s = pathcat(path, mangle(name, level, label));
  elems[nelems].type = type;
  elems[nelems].label = strdup(s.c_str());
  elems[nelems].zone = zone;
  elems[nelems].init = init;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = step;
  nelems++;
}

inline void PdUI::add_elem(ui_elem_type_t type, const char *label, float *zone,
			  float min, float max)
{
  ui_elem_t *elems1 = (ui_elem_t*)realloc(elems, (nelems+1)*sizeof(ui_elem_t));
  if (elems1)
    elems = elems1;
  else
    return;
  std::string s = pathcat(path, mangle(name, level, label));
  elems[nelems].type = type;
  elems[nelems].label = strdup(s.c_str());
  elems[nelems].zone = zone;
  elems[nelems].init = 0.0;
  elems[nelems].min = min;
  elems[nelems].max = max;
  elems[nelems].step = 0.0;
  nelems++;
}

void PdUI::addButton(const char* label, float* zone)
{ add_elem(UI_BUTTON, label, zone); }
void PdUI::addCheckButton(const char* label, float* zone)
{ add_elem(UI_CHECK_BUTTON, label, zone); }
void PdUI::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_V_SLIDER, label, zone, init, min, max, step); }
void PdUI::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_H_SLIDER, label, zone, init, min, max, step); }
void PdUI::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{ add_elem(UI_NUM_ENTRY, label, zone, init, min, max, step); }

void PdUI::addHorizontalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_H_BARGRAPH, label, zone, min, max); }
void PdUI::addVerticalBargraph(const char* label, float* zone, float min, float max)
{ add_elem(UI_V_BARGRAPH, label, zone, min, max); }

void PdUI::openTabBox(const char* label)
{
  if (!path.empty()) path += "/";
  path += mangle(name, level, label);
  level++;
}
void PdUI::openHorizontalBox(const char* label)
{
  if (!path.empty()) path += "/";
  path += mangle(name, level, label);
  level++;
}
void PdUI::openVerticalBox(const char* label)
{
  if (!path.empty()) path += "/";
  path += mangle(name, level, label);
  level++;
}
void PdUI::closeBox()
{
  int pos = path.rfind("/");
  if (pos < 0) pos = 0;
  path.erase(pos);
  level--;
}

void PdUI::run() {}

/******************************************************************************
*******************************************************************************

			    FAUST DSP

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------
		
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	class SIG0 {
	  private:
		int fSamplingFreq;
		static int 	iWave0[1302];
		int 	idxiWave0;
	  public:
		int getNumInputs() { return 0; }
		int getNumOutputs() { return 1; }
		void init(int samplingFreq) {
			fSamplingFreq = samplingFreq;
			idxiWave0 = 0;
		}
		void fill (int count, int output[]) {
			for (int i=0; i<count; i++) {
				output[i] = iWave0[idxiWave0];
				// post processing
				idxiWave0 = (idxiWave0 + 1) % 1302;
			}
		}
	};


	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	float 	fVec1[2];
	float 	fConst0;
	float 	fConst1;
	float 	fRec3[2];
	float 	fRec4[2];
	FAUSTFLOAT 	fslider1;
	float 	fVec2[2];
	float 	fConst2;
	int 	IOTA;
	float 	fVec3[65536];
	FAUSTFLOAT 	fslider2;
	float 	fRec5[2];
	float 	fRec6[2];
	float 	fRec7[2];
	float 	fRec8[2];
	FAUSTFLOAT 	fslider3;
	float 	fVec4[2];
	FAUSTFLOAT 	fslider4;
	float 	fVec5[2];
	static int 	itbl0[1302];
	FAUSTFLOAT 	fslider5;
	float 	fRec12[2];
	float 	fVec6[65536];
	float 	fRec16[2];
	float 	fRec20[2];
	float 	fRec24[2];
	float 	fVec7[16384];
	float 	fRec23[2];
	float 	fRec21[2];
	float 	fRec26[2];
	float 	fVec8[16384];
	float 	fRec25[2];
	float 	fRec22[2];
	float 	fVec9[16384];
	float 	fRec19[2];
	float 	fRec17[2];
	float 	fRec28[2];
	float 	fVec10[16384];
	float 	fRec27[2];
	float 	fRec18[2];
	float 	fVec11[16384];
	float 	fRec15[2];
	float 	fRec13[2];
	float 	fRec30[2];
	float 	fVec12[16384];
	float 	fRec29[2];
	float 	fRec14[2];
	float 	fVec13[16384];
	float 	fRec11[2];
	float 	fRec9[2];
	float 	fRec32[2];
	float 	fVec14[16384];
	float 	fRec31[2];
	float 	fRec10[2];
	float 	fRec36[2];
	float 	fVec15[16384];
	float 	fRec48[2];
	float 	fRec46[2];
	float 	fVec16[16384];
	float 	fRec49[2];
	float 	fRec47[2];
	float 	fVec17[16384];
	float 	fRec45[2];
	float 	fRec43[2];
	float 	fVec18[16384];
	float 	fRec50[2];
	float 	fRec44[2];
	float 	fVec19[16384];
	float 	fRec42[2];
	float 	fRec40[2];
	float 	fVec20[16384];
	float 	fRec51[2];
	float 	fRec41[2];
	float 	fVec21[16384];
	float 	fRec39[2];
	float 	fRec37[2];
	float 	fVec22[16384];
	float 	fRec52[2];
	float 	fRec38[2];
	float 	fRec56[2];
	float 	fVec23[16384];
	float 	fRec68[2];
	float 	fRec66[2];
	float 	fVec24[16384];
	float 	fRec69[2];
	float 	fRec67[2];
	float 	fVec25[16384];
	float 	fRec65[2];
	float 	fRec63[2];
	float 	fVec26[16384];
	float 	fRec70[2];
	float 	fRec64[2];
	float 	fVec27[16384];
	float 	fRec62[2];
	float 	fRec60[2];
	float 	fVec28[16384];
	float 	fRec71[2];
	float 	fRec61[2];
	float 	fVec29[16384];
	float 	fRec59[2];
	float 	fRec57[2];
	float 	fVec30[16384];
	float 	fRec72[2];
	float 	fRec58[2];
	float 	fRec76[2];
	float 	fRec80[2];
	float 	fVec31[16384];
	float 	fRec92[2];
	float 	fRec90[2];
	float 	fVec32[16384];
	float 	fRec93[2];
	float 	fRec91[2];
	float 	fVec33[16384];
	float 	fRec89[2];
	float 	fRec87[2];
	float 	fVec34[16384];
	float 	fRec94[2];
	float 	fRec88[2];
	float 	fVec35[16384];
	float 	fRec86[2];
	float 	fRec84[2];
	float 	fVec36[16384];
	float 	fRec95[2];
	float 	fRec85[2];
	float 	fVec37[16384];
	float 	fRec83[2];
	float 	fRec81[2];
	float 	fVec38[16384];
	float 	fRec96[2];
	float 	fRec82[2];
	float 	fVec39[16384];
	float 	fRec79[2];
	float 	fRec77[2];
	float 	fRec98[2];
	float 	fVec40[16384];
	float 	fRec97[2];
	float 	fRec78[2];
	float 	fVec41[16384];
	float 	fRec75[2];
	float 	fRec73[2];
	float 	fRec100[2];
	float 	fVec42[16384];
	float 	fRec99[2];
	float 	fRec74[2];
	float 	fVec43[16384];
	float 	fRec55[2];
	float 	fRec53[2];
	float 	fRec102[2];
	float 	fVec44[16384];
	float 	fRec101[2];
	float 	fRec54[2];
	float 	fVec45[16384];
	float 	fRec35[2];
	float 	fRec33[2];
	float 	fRec104[2];
	float 	fVec46[16384];
	float 	fRec103[2];
	float 	fRec34[2];
	float 	fVec47[16384];
	float 	fRec131[2];
	float 	fRec129[2];
	float 	fVec48[16384];
	float 	fRec132[2];
	float 	fRec130[2];
	float 	fVec49[16384];
	float 	fRec128[2];
	float 	fRec126[2];
	float 	fVec50[16384];
	float 	fRec133[2];
	float 	fRec127[2];
	float 	fVec51[16384];
	float 	fRec125[2];
	float 	fRec123[2];
	float 	fVec52[16384];
	float 	fRec134[2];
	float 	fRec124[2];
	float 	fVec53[16384];
	float 	fRec122[2];
	float 	fRec120[2];
	float 	fVec54[16384];
	float 	fRec135[2];
	float 	fRec121[2];
	float 	fVec55[16384];
	float 	fRec119[2];
	float 	fRec117[2];
	float 	fVec56[16384];
	float 	fRec136[2];
	float 	fRec118[2];
	float 	fVec57[16384];
	float 	fRec116[2];
	float 	fRec114[2];
	float 	fVec58[16384];
	float 	fRec137[2];
	float 	fRec115[2];
	float 	fVec59[16384];
	float 	fRec113[2];
	float 	fRec111[2];
	float 	fVec60[16384];
	float 	fRec138[2];
	float 	fRec112[2];
	float 	fVec61[16384];
	float 	fRec110[2];
	float 	fRec108[2];
	float 	fVec62[16384];
	float 	fRec139[2];
	float 	fRec109[2];
	float 	fVec63[16384];
	float 	fRec154[2];
	float 	fRec152[2];
	float 	fVec64[16384];
	float 	fRec155[2];
	float 	fRec153[2];
	float 	fVec65[16384];
	float 	fRec151[2];
	float 	fRec149[2];
	float 	fVec66[16384];
	float 	fRec156[2];
	float 	fRec150[2];
	float 	fVec67[16384];
	float 	fRec148[2];
	float 	fRec146[2];
	float 	fVec68[16384];
	float 	fRec157[2];
	float 	fRec147[2];
	float 	fVec69[16384];
	float 	fRec145[2];
	float 	fRec143[2];
	float 	fVec70[16384];
	float 	fRec158[2];
	float 	fRec144[2];
	float 	fVec71[16384];
	float 	fRec173[2];
	float 	fRec171[2];
	float 	fVec72[16384];
	float 	fRec174[2];
	float 	fRec172[2];
	float 	fVec73[16384];
	float 	fRec170[2];
	float 	fRec168[2];
	float 	fVec74[16384];
	float 	fRec175[2];
	float 	fRec169[2];
	float 	fVec75[16384];
	float 	fRec167[2];
	float 	fRec165[2];
	float 	fVec76[16384];
	float 	fRec176[2];
	float 	fRec166[2];
	float 	fVec77[16384];
	float 	fRec164[2];
	float 	fRec162[2];
	float 	fVec78[16384];
	float 	fRec177[2];
	float 	fRec163[2];
	float 	fVec79[16384];
	float 	fRec204[2];
	float 	fRec202[2];
	float 	fVec80[16384];
	float 	fRec205[2];
	float 	fRec203[2];
	float 	fVec81[16384];
	float 	fRec201[2];
	float 	fRec199[2];
	float 	fVec82[16384];
	float 	fRec206[2];
	float 	fRec200[2];
	float 	fVec83[16384];
	float 	fRec198[2];
	float 	fRec196[2];
	float 	fVec84[16384];
	float 	fRec207[2];
	float 	fRec197[2];
	float 	fVec85[16384];
	float 	fRec195[2];
	float 	fRec193[2];
	float 	fVec86[16384];
	float 	fRec208[2];
	float 	fRec194[2];
	float 	fVec87[16384];
	float 	fRec192[2];
	float 	fRec190[2];
	float 	fVec88[16384];
	float 	fRec209[2];
	float 	fRec191[2];
	float 	fVec89[16384];
	float 	fRec189[2];
	float 	fRec187[2];
	float 	fVec90[16384];
	float 	fRec210[2];
	float 	fRec188[2];
	float 	fVec91[16384];
	float 	fRec186[2];
	float 	fRec184[2];
	float 	fVec92[16384];
	float 	fRec211[2];
	float 	fRec185[2];
	float 	fVec93[16384];
	float 	fRec183[2];
	float 	fRec181[2];
	float 	fVec94[16384];
	float 	fRec212[2];
	float 	fRec182[2];
	float 	fVec95[16384];
	float 	fRec213[2];
	float 	fRec180[2];
	float 	fRec178[2];
	float 	fVec96[16384];
	float 	fRec215[2];
	float 	fRec214[2];
	float 	fRec179[2];
	float 	fVec97[16384];
	float 	fRec216[2];
	float 	fRec161[2];
	float 	fRec159[2];
	float 	fVec98[16384];
	float 	fRec218[2];
	float 	fRec217[2];
	float 	fRec160[2];
	float 	fVec99[16384];
	float 	fRec219[2];
	float 	fRec142[2];
	float 	fRec140[2];
	float 	fVec100[16384];
	float 	fRec221[2];
	float 	fRec220[2];
	float 	fRec141[2];
	float 	fVec101[16384];
	float 	fRec222[2];
	float 	fRec107[2];
	float 	fRec105[2];
	float 	fVec102[16384];
	float 	fRec224[2];
	float 	fRec223[2];
	float 	fRec106[2];
	FAUSTFLOAT 	fslider6;
	float 	fVec103[2];
	float 	fRec2[2];
	float 	fRec0[1024];
	float 	fRec225[2];
	float 	fRec1[1024];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("name", "GreyholeRaw");
		m->declare("version", "1.0");
		m->declare("author", "Julian Parker, bug fixes by Till Bovermann");
		m->declare("license", "GPL2+");
		m->declare("copyright", "(c) Julian Parker 2013");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("delay.lib/name", "Faust Delay Library");
		m->declare("delay.lib/version", "0.0");
		m->declare("miscoscillator.lib/name", "Faust Oscillator Library");
		m->declare("miscoscillator.lib/version", "0.0");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/version", "2.0");
		m->declare("signal.lib/name", "Faust Signal Routing Library");
		m->declare("signal.lib/version", "0.0");
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 2; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
		SIG0 sig0;
		sig0.init(samplingFreq);
		sig0.fill(1302,itbl0);
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.1415927f / fConst0);
		fConst2 = (0.00056689343f * fConst0);
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 2.0f;
		fslider1 = 0.1f;
		fslider2 = 0.2f;
		fslider3 = 0.9f;
		fslider4 = 0.5f;
		fslider5 = 1.0f;
		fslider6 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		IOTA = 0;
		for (int i=0; i<65536; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<65536; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<16384; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<16384; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<16384; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<16384; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<16384; i++) fVec11[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<16384; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<16384; i++) fVec13[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<16384; i++) fVec14[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<16384; i++) fVec15[i] = 0;
		for (int i=0; i<2; i++) fRec48[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<16384; i++) fVec16[i] = 0;
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<16384; i++) fVec17[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<16384; i++) fVec18[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2; i++) fRec44[i] = 0;
		for (int i=0; i<16384; i++) fVec19[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<16384; i++) fVec20[i] = 0;
		for (int i=0; i<2; i++) fRec51[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<16384; i++) fVec21[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<16384; i++) fVec22[i] = 0;
		for (int i=0; i<2; i++) fRec52[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) fRec56[i] = 0;
		for (int i=0; i<16384; i++) fVec23[i] = 0;
		for (int i=0; i<2; i++) fRec68[i] = 0;
		for (int i=0; i<2; i++) fRec66[i] = 0;
		for (int i=0; i<16384; i++) fVec24[i] = 0;
		for (int i=0; i<2; i++) fRec69[i] = 0;
		for (int i=0; i<2; i++) fRec67[i] = 0;
		for (int i=0; i<16384; i++) fVec25[i] = 0;
		for (int i=0; i<2; i++) fRec65[i] = 0;
		for (int i=0; i<2; i++) fRec63[i] = 0;
		for (int i=0; i<16384; i++) fVec26[i] = 0;
		for (int i=0; i<2; i++) fRec70[i] = 0;
		for (int i=0; i<2; i++) fRec64[i] = 0;
		for (int i=0; i<16384; i++) fVec27[i] = 0;
		for (int i=0; i<2; i++) fRec62[i] = 0;
		for (int i=0; i<2; i++) fRec60[i] = 0;
		for (int i=0; i<16384; i++) fVec28[i] = 0;
		for (int i=0; i<2; i++) fRec71[i] = 0;
		for (int i=0; i<2; i++) fRec61[i] = 0;
		for (int i=0; i<16384; i++) fVec29[i] = 0;
		for (int i=0; i<2; i++) fRec59[i] = 0;
		for (int i=0; i<2; i++) fRec57[i] = 0;
		for (int i=0; i<16384; i++) fVec30[i] = 0;
		for (int i=0; i<2; i++) fRec72[i] = 0;
		for (int i=0; i<2; i++) fRec58[i] = 0;
		for (int i=0; i<2; i++) fRec76[i] = 0;
		for (int i=0; i<2; i++) fRec80[i] = 0;
		for (int i=0; i<16384; i++) fVec31[i] = 0;
		for (int i=0; i<2; i++) fRec92[i] = 0;
		for (int i=0; i<2; i++) fRec90[i] = 0;
		for (int i=0; i<16384; i++) fVec32[i] = 0;
		for (int i=0; i<2; i++) fRec93[i] = 0;
		for (int i=0; i<2; i++) fRec91[i] = 0;
		for (int i=0; i<16384; i++) fVec33[i] = 0;
		for (int i=0; i<2; i++) fRec89[i] = 0;
		for (int i=0; i<2; i++) fRec87[i] = 0;
		for (int i=0; i<16384; i++) fVec34[i] = 0;
		for (int i=0; i<2; i++) fRec94[i] = 0;
		for (int i=0; i<2; i++) fRec88[i] = 0;
		for (int i=0; i<16384; i++) fVec35[i] = 0;
		for (int i=0; i<2; i++) fRec86[i] = 0;
		for (int i=0; i<2; i++) fRec84[i] = 0;
		for (int i=0; i<16384; i++) fVec36[i] = 0;
		for (int i=0; i<2; i++) fRec95[i] = 0;
		for (int i=0; i<2; i++) fRec85[i] = 0;
		for (int i=0; i<16384; i++) fVec37[i] = 0;
		for (int i=0; i<2; i++) fRec83[i] = 0;
		for (int i=0; i<2; i++) fRec81[i] = 0;
		for (int i=0; i<16384; i++) fVec38[i] = 0;
		for (int i=0; i<2; i++) fRec96[i] = 0;
		for (int i=0; i<2; i++) fRec82[i] = 0;
		for (int i=0; i<16384; i++) fVec39[i] = 0;
		for (int i=0; i<2; i++) fRec79[i] = 0;
		for (int i=0; i<2; i++) fRec77[i] = 0;
		for (int i=0; i<2; i++) fRec98[i] = 0;
		for (int i=0; i<16384; i++) fVec40[i] = 0;
		for (int i=0; i<2; i++) fRec97[i] = 0;
		for (int i=0; i<2; i++) fRec78[i] = 0;
		for (int i=0; i<16384; i++) fVec41[i] = 0;
		for (int i=0; i<2; i++) fRec75[i] = 0;
		for (int i=0; i<2; i++) fRec73[i] = 0;
		for (int i=0; i<2; i++) fRec100[i] = 0;
		for (int i=0; i<16384; i++) fVec42[i] = 0;
		for (int i=0; i<2; i++) fRec99[i] = 0;
		for (int i=0; i<2; i++) fRec74[i] = 0;
		for (int i=0; i<16384; i++) fVec43[i] = 0;
		for (int i=0; i<2; i++) fRec55[i] = 0;
		for (int i=0; i<2; i++) fRec53[i] = 0;
		for (int i=0; i<2; i++) fRec102[i] = 0;
		for (int i=0; i<16384; i++) fVec44[i] = 0;
		for (int i=0; i<2; i++) fRec101[i] = 0;
		for (int i=0; i<2; i++) fRec54[i] = 0;
		for (int i=0; i<16384; i++) fVec45[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec104[i] = 0;
		for (int i=0; i<16384; i++) fVec46[i] = 0;
		for (int i=0; i<2; i++) fRec103[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<16384; i++) fVec47[i] = 0;
		for (int i=0; i<2; i++) fRec131[i] = 0;
		for (int i=0; i<2; i++) fRec129[i] = 0;
		for (int i=0; i<16384; i++) fVec48[i] = 0;
		for (int i=0; i<2; i++) fRec132[i] = 0;
		for (int i=0; i<2; i++) fRec130[i] = 0;
		for (int i=0; i<16384; i++) fVec49[i] = 0;
		for (int i=0; i<2; i++) fRec128[i] = 0;
		for (int i=0; i<2; i++) fRec126[i] = 0;
		for (int i=0; i<16384; i++) fVec50[i] = 0;
		for (int i=0; i<2; i++) fRec133[i] = 0;
		for (int i=0; i<2; i++) fRec127[i] = 0;
		for (int i=0; i<16384; i++) fVec51[i] = 0;
		for (int i=0; i<2; i++) fRec125[i] = 0;
		for (int i=0; i<2; i++) fRec123[i] = 0;
		for (int i=0; i<16384; i++) fVec52[i] = 0;
		for (int i=0; i<2; i++) fRec134[i] = 0;
		for (int i=0; i<2; i++) fRec124[i] = 0;
		for (int i=0; i<16384; i++) fVec53[i] = 0;
		for (int i=0; i<2; i++) fRec122[i] = 0;
		for (int i=0; i<2; i++) fRec120[i] = 0;
		for (int i=0; i<16384; i++) fVec54[i] = 0;
		for (int i=0; i<2; i++) fRec135[i] = 0;
		for (int i=0; i<2; i++) fRec121[i] = 0;
		for (int i=0; i<16384; i++) fVec55[i] = 0;
		for (int i=0; i<2; i++) fRec119[i] = 0;
		for (int i=0; i<2; i++) fRec117[i] = 0;
		for (int i=0; i<16384; i++) fVec56[i] = 0;
		for (int i=0; i<2; i++) fRec136[i] = 0;
		for (int i=0; i<2; i++) fRec118[i] = 0;
		for (int i=0; i<16384; i++) fVec57[i] = 0;
		for (int i=0; i<2; i++) fRec116[i] = 0;
		for (int i=0; i<2; i++) fRec114[i] = 0;
		for (int i=0; i<16384; i++) fVec58[i] = 0;
		for (int i=0; i<2; i++) fRec137[i] = 0;
		for (int i=0; i<2; i++) fRec115[i] = 0;
		for (int i=0; i<16384; i++) fVec59[i] = 0;
		for (int i=0; i<2; i++) fRec113[i] = 0;
		for (int i=0; i<2; i++) fRec111[i] = 0;
		for (int i=0; i<16384; i++) fVec60[i] = 0;
		for (int i=0; i<2; i++) fRec138[i] = 0;
		for (int i=0; i<2; i++) fRec112[i] = 0;
		for (int i=0; i<16384; i++) fVec61[i] = 0;
		for (int i=0; i<2; i++) fRec110[i] = 0;
		for (int i=0; i<2; i++) fRec108[i] = 0;
		for (int i=0; i<16384; i++) fVec62[i] = 0;
		for (int i=0; i<2; i++) fRec139[i] = 0;
		for (int i=0; i<2; i++) fRec109[i] = 0;
		for (int i=0; i<16384; i++) fVec63[i] = 0;
		for (int i=0; i<2; i++) fRec154[i] = 0;
		for (int i=0; i<2; i++) fRec152[i] = 0;
		for (int i=0; i<16384; i++) fVec64[i] = 0;
		for (int i=0; i<2; i++) fRec155[i] = 0;
		for (int i=0; i<2; i++) fRec153[i] = 0;
		for (int i=0; i<16384; i++) fVec65[i] = 0;
		for (int i=0; i<2; i++) fRec151[i] = 0;
		for (int i=0; i<2; i++) fRec149[i] = 0;
		for (int i=0; i<16384; i++) fVec66[i] = 0;
		for (int i=0; i<2; i++) fRec156[i] = 0;
		for (int i=0; i<2; i++) fRec150[i] = 0;
		for (int i=0; i<16384; i++) fVec67[i] = 0;
		for (int i=0; i<2; i++) fRec148[i] = 0;
		for (int i=0; i<2; i++) fRec146[i] = 0;
		for (int i=0; i<16384; i++) fVec68[i] = 0;
		for (int i=0; i<2; i++) fRec157[i] = 0;
		for (int i=0; i<2; i++) fRec147[i] = 0;
		for (int i=0; i<16384; i++) fVec69[i] = 0;
		for (int i=0; i<2; i++) fRec145[i] = 0;
		for (int i=0; i<2; i++) fRec143[i] = 0;
		for (int i=0; i<16384; i++) fVec70[i] = 0;
		for (int i=0; i<2; i++) fRec158[i] = 0;
		for (int i=0; i<2; i++) fRec144[i] = 0;
		for (int i=0; i<16384; i++) fVec71[i] = 0;
		for (int i=0; i<2; i++) fRec173[i] = 0;
		for (int i=0; i<2; i++) fRec171[i] = 0;
		for (int i=0; i<16384; i++) fVec72[i] = 0;
		for (int i=0; i<2; i++) fRec174[i] = 0;
		for (int i=0; i<2; i++) fRec172[i] = 0;
		for (int i=0; i<16384; i++) fVec73[i] = 0;
		for (int i=0; i<2; i++) fRec170[i] = 0;
		for (int i=0; i<2; i++) fRec168[i] = 0;
		for (int i=0; i<16384; i++) fVec74[i] = 0;
		for (int i=0; i<2; i++) fRec175[i] = 0;
		for (int i=0; i<2; i++) fRec169[i] = 0;
		for (int i=0; i<16384; i++) fVec75[i] = 0;
		for (int i=0; i<2; i++) fRec167[i] = 0;
		for (int i=0; i<2; i++) fRec165[i] = 0;
		for (int i=0; i<16384; i++) fVec76[i] = 0;
		for (int i=0; i<2; i++) fRec176[i] = 0;
		for (int i=0; i<2; i++) fRec166[i] = 0;
		for (int i=0; i<16384; i++) fVec77[i] = 0;
		for (int i=0; i<2; i++) fRec164[i] = 0;
		for (int i=0; i<2; i++) fRec162[i] = 0;
		for (int i=0; i<16384; i++) fVec78[i] = 0;
		for (int i=0; i<2; i++) fRec177[i] = 0;
		for (int i=0; i<2; i++) fRec163[i] = 0;
		for (int i=0; i<16384; i++) fVec79[i] = 0;
		for (int i=0; i<2; i++) fRec204[i] = 0;
		for (int i=0; i<2; i++) fRec202[i] = 0;
		for (int i=0; i<16384; i++) fVec80[i] = 0;
		for (int i=0; i<2; i++) fRec205[i] = 0;
		for (int i=0; i<2; i++) fRec203[i] = 0;
		for (int i=0; i<16384; i++) fVec81[i] = 0;
		for (int i=0; i<2; i++) fRec201[i] = 0;
		for (int i=0; i<2; i++) fRec199[i] = 0;
		for (int i=0; i<16384; i++) fVec82[i] = 0;
		for (int i=0; i<2; i++) fRec206[i] = 0;
		for (int i=0; i<2; i++) fRec200[i] = 0;
		for (int i=0; i<16384; i++) fVec83[i] = 0;
		for (int i=0; i<2; i++) fRec198[i] = 0;
		for (int i=0; i<2; i++) fRec196[i] = 0;
		for (int i=0; i<16384; i++) fVec84[i] = 0;
		for (int i=0; i<2; i++) fRec207[i] = 0;
		for (int i=0; i<2; i++) fRec197[i] = 0;
		for (int i=0; i<16384; i++) fVec85[i] = 0;
		for (int i=0; i<2; i++) fRec195[i] = 0;
		for (int i=0; i<2; i++) fRec193[i] = 0;
		for (int i=0; i<16384; i++) fVec86[i] = 0;
		for (int i=0; i<2; i++) fRec208[i] = 0;
		for (int i=0; i<2; i++) fRec194[i] = 0;
		for (int i=0; i<16384; i++) fVec87[i] = 0;
		for (int i=0; i<2; i++) fRec192[i] = 0;
		for (int i=0; i<2; i++) fRec190[i] = 0;
		for (int i=0; i<16384; i++) fVec88[i] = 0;
		for (int i=0; i<2; i++) fRec209[i] = 0;
		for (int i=0; i<2; i++) fRec191[i] = 0;
		for (int i=0; i<16384; i++) fVec89[i] = 0;
		for (int i=0; i<2; i++) fRec189[i] = 0;
		for (int i=0; i<2; i++) fRec187[i] = 0;
		for (int i=0; i<16384; i++) fVec90[i] = 0;
		for (int i=0; i<2; i++) fRec210[i] = 0;
		for (int i=0; i<2; i++) fRec188[i] = 0;
		for (int i=0; i<16384; i++) fVec91[i] = 0;
		for (int i=0; i<2; i++) fRec186[i] = 0;
		for (int i=0; i<2; i++) fRec184[i] = 0;
		for (int i=0; i<16384; i++) fVec92[i] = 0;
		for (int i=0; i<2; i++) fRec211[i] = 0;
		for (int i=0; i<2; i++) fRec185[i] = 0;
		for (int i=0; i<16384; i++) fVec93[i] = 0;
		for (int i=0; i<2; i++) fRec183[i] = 0;
		for (int i=0; i<2; i++) fRec181[i] = 0;
		for (int i=0; i<16384; i++) fVec94[i] = 0;
		for (int i=0; i<2; i++) fRec212[i] = 0;
		for (int i=0; i<2; i++) fRec182[i] = 0;
		for (int i=0; i<16384; i++) fVec95[i] = 0;
		for (int i=0; i<2; i++) fRec213[i] = 0;
		for (int i=0; i<2; i++) fRec180[i] = 0;
		for (int i=0; i<2; i++) fRec178[i] = 0;
		for (int i=0; i<16384; i++) fVec96[i] = 0;
		for (int i=0; i<2; i++) fRec215[i] = 0;
		for (int i=0; i<2; i++) fRec214[i] = 0;
		for (int i=0; i<2; i++) fRec179[i] = 0;
		for (int i=0; i<16384; i++) fVec97[i] = 0;
		for (int i=0; i<2; i++) fRec216[i] = 0;
		for (int i=0; i<2; i++) fRec161[i] = 0;
		for (int i=0; i<2; i++) fRec159[i] = 0;
		for (int i=0; i<16384; i++) fVec98[i] = 0;
		for (int i=0; i<2; i++) fRec218[i] = 0;
		for (int i=0; i<2; i++) fRec217[i] = 0;
		for (int i=0; i<2; i++) fRec160[i] = 0;
		for (int i=0; i<16384; i++) fVec99[i] = 0;
		for (int i=0; i<2; i++) fRec219[i] = 0;
		for (int i=0; i<2; i++) fRec142[i] = 0;
		for (int i=0; i<2; i++) fRec140[i] = 0;
		for (int i=0; i<16384; i++) fVec100[i] = 0;
		for (int i=0; i<2; i++) fRec221[i] = 0;
		for (int i=0; i<2; i++) fRec220[i] = 0;
		for (int i=0; i<2; i++) fRec141[i] = 0;
		for (int i=0; i<16384; i++) fVec101[i] = 0;
		for (int i=0; i<2; i++) fRec222[i] = 0;
		for (int i=0; i<2; i++) fRec107[i] = 0;
		for (int i=0; i<2; i++) fRec105[i] = 0;
		for (int i=0; i<16384; i++) fVec102[i] = 0;
		for (int i=0; i<2; i++) fRec224[i] = 0;
		for (int i=0; i<2; i++) fRec223[i] = 0;
		for (int i=0; i<2; i++) fRec106[i] = 0;
		for (int i=0; i<2; i++) fVec103[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<1024; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec225[i] = 0;
		for (int i=0; i<1024; i++) fRec1[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual mydsp* clone() {
		return new mydsp();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("0x00");
		ui_interface->addHorizontalSlider("damping", &fslider6, 0.0f, 0.0f, 0.99f, 0.001f);
		ui_interface->addHorizontalSlider("delayTime", &fslider2, 0.2f, 0.001f, 1.45f, 0.0001f);
		ui_interface->addHorizontalSlider("diffusion", &fslider4, 0.5f, 0.0f, 0.99f, 0.0001f);
		ui_interface->addHorizontalSlider("feedback", &fslider3, 0.9f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("modDepth", &fslider1, 0.1f, 0.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("modFreq", &fslider0, 2.0f, 0.0f, 1e+01f, 0.01f);
		ui_interface->addHorizontalSlider("size", &fslider5, 1.0f, 0.5f, 3.0f, 0.0001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = floorf(min((float)65533, (fConst0 * float(fslider2))));
		float 	fSlow3 = float(fslider3);
		float 	fSlow4 = float(fslider4);
		float 	fSlow5 = float(fslider5);
		int 	iSlow6 = int((10 * fSlow5));
		float 	fSlow7 = (23 * fSlow5);
		int 	iSlow8 = int(fSlow7);
		float 	fSlow9 = (36 * fSlow5);
		int 	iSlow10 = int(fSlow9);
		float 	fSlow11 = (49 * fSlow5);
		int 	iSlow12 = int(fSlow11);
		int 	iSlow13 = int((fSlow11 + 10));
		int 	iSlow14 = int((fSlow9 + 10));
		int 	iSlow15 = int((fSlow7 + 10));
		int 	iSlow16 = int((10 * (fSlow5 + 1)));
		float 	fSlow17 = (29 * fSlow5);
		int 	iSlow18 = int(fSlow17);
		float 	fSlow19 = (42 * fSlow5);
		int 	iSlow20 = int(fSlow19);
		float 	fSlow21 = (55 * fSlow5);
		int 	iSlow22 = int(fSlow21);
		float 	fSlow23 = (68 * fSlow5);
		int 	iSlow24 = int(fSlow23);
		int 	iSlow25 = int((fSlow23 + 10));
		int 	iSlow26 = int((fSlow21 + 10));
		int 	iSlow27 = int((fSlow19 + 10));
		int 	iSlow28 = int((fSlow17 + 10));
		float 	fSlow29 = (87 * fSlow5);
		int 	iSlow30 = int(fSlow29);
		int 	iSlow31 = int((fSlow29 + 10));
		float 	fSlow32 = (74 * fSlow5);
		int 	iSlow33 = int(fSlow32);
		int 	iSlow34 = int((fSlow32 + 10));
		float 	fSlow35 = (61 * fSlow5);
		int 	iSlow36 = int(fSlow35);
		int 	iSlow37 = int((fSlow35 + 10));
		float 	fSlow38 = (48 * fSlow5);
		int 	iSlow39 = int(fSlow38);
		int 	iSlow40 = int((fSlow38 + 10));
		float 	fSlow41 = float(fslider6);
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fVec1[0] = fSlow0;
			float fTemp0 = (fConst1 * (fSlow0 + fVec1[1]));
			float fTemp1 = cosf(fTemp0);
			float fTemp2 = sinf(fTemp0);
			fRec3[0] = ((fTemp2 * fRec4[1]) + (fTemp1 * fRec3[1]));
			int iTemp3 = (1 - iVec0[1]);
			fRec4[0] = (((fTemp1 * fRec4[1]) + ((0 - fTemp2) * fRec3[1])) + iTemp3);
			fVec2[0] = fSlow1;
			float fTemp4 = (fSlow1 + fVec2[1]);
			float fTemp5 = (fConst2 * (fTemp4 * (fRec4[0] + 1.0f)));
			float fTemp6 = (fTemp5 + 8.500005f);
			int iTemp7 = int(fTemp6);
			float fTemp8 = floorf(fTemp6);
			float fTemp9 = (fTemp5 + (7.0f - fTemp8));
			float fTemp10 = (fTemp5 + (8.0f - fTemp8));
			float fTemp11 = (fTemp5 + (6.0f - fTemp8));
			float fTemp12 = (((((fRec0[(IOTA-int((int((iTemp7 & 511)) + 1)))&1023] * (0 - (0.5f * fTemp10))) * (0 - (0.33333334f * fTemp9))) * (0 - (0.25f * fTemp11))) * (fTemp8 + (-9.0f - fTemp5))) + ((fTemp5 + (1e+01f - fTemp8)) * ((((fRec0[(IOTA-int((int((int((iTemp7 + 1)) & 511)) + 1)))&1023] * (0 - (0.5f * fTemp9))) * (0 - (0.33333334f * fTemp11))) * (fTemp8 + (-8.0f - fTemp5))) + ((fTemp5 + (9.0f - fTemp8)) * (((0.5f * ((fRec0[(IOTA-int((int((int((iTemp7 + 2)) & 511)) + 1)))&1023] * (0 - (0.5f * fTemp11))) * (fTemp8 + (-7.0f - fTemp5)))) + (0.16666667f * ((fTemp10 * fRec0[(IOTA-int((int((int((iTemp7 + 3)) & 511)) + 1)))&1023]) * (fTemp8 + (-6.0f - fTemp5))))) + (0.041666668f * ((fTemp10 * fTemp9) * fRec0[(IOTA-int((int((int((iTemp7 + 4)) & 511)) + 1)))&1023])))))));
			fVec3[IOTA&65535] = fTemp12;
			float fTemp13 = ((int((fRec5[1] != 0.0f)))?((int(((fRec6[1] > 0.0f) & (fRec6[1] < 1.0f))))?fRec5[1]:0):((int(((fRec6[1] == 0.0f) & (fSlow2 != fRec7[1]))))?4.5351473e-05f:((int(((fRec6[1] == 1.0f) & (fSlow2 != fRec8[1]))))?-4.5351473e-05f:0)));
			fRec5[0] = fTemp13;
			fRec6[0] = max(0.0f, min(1.0f, (fRec6[1] + fTemp13)));
			fRec7[0] = ((int(((fRec6[1] >= 1.0f) & (fRec8[1] != fSlow2))))?fSlow2:fRec7[1]);
			fRec8[0] = ((int(((fRec6[1] <= 0.0f) & (fRec7[1] != fSlow2))))?fSlow2:fRec8[1]);
			int iTemp14 = int((int(fRec8[0]) & 65535));
			int iTemp15 = int((int(fRec7[0]) & 65535));
			float fTemp16 = (1.0f - fRec6[0]);
			fVec4[0] = fSlow3;
			float fTemp17 = (fSlow3 + fVec4[1]);
			float fTemp18 = ((float)input0[i] + (0.5f * (fTemp17 * ((fTemp16 * fVec3[(IOTA-iTemp15)&65535]) + (fRec6[0] * fVec3[(IOTA-iTemp14)&65535])))));
			fVec5[0] = fSlow4;
			float fTemp19 = (0.5f * (fSlow4 + fVec5[1]));
			float fTemp20 = sinf(fTemp19);
			float fTemp21 = (fTemp20 * fTemp18);
			int iTemp22 = itbl0[iSlow6];
			fRec12[0] = ((0.001f * iTemp22) + (0.999f * ((iTemp3 * iTemp22) + fRec12[1])));
			float fTemp23 = (fRec12[0] + -1.49999f);
			float fTemp24 = floorf(fTemp23);
			float fTemp25 = (fRec12[0] - fTemp24);
			float fTemp26 = (fTemp24 + (2.0f - fRec12[0]));
			float fTemp27 = (0 - (fTemp26 / fTemp25));
			float fTemp28 = (fConst2 * (fTemp4 * (fRec3[0] + 1.0f)));
			float fTemp29 = (fTemp28 + 8.500005f);
			int iTemp30 = int(fTemp29);
			float fTemp31 = floorf(fTemp29);
			float fTemp32 = (fTemp28 + (7.0f - fTemp31));
			float fTemp33 = (fTemp28 + (8.0f - fTemp31));
			float fTemp34 = (fTemp28 + (6.0f - fTemp31));
			float fTemp35 = (((((fRec1[(IOTA-int((int((iTemp30 & 511)) + 1)))&1023] * (0 - (0.5f * fTemp33))) * (0 - (0.33333334f * fTemp32))) * (0 - (0.25f * fTemp34))) * (fTemp31 + (-9.0f - fTemp28))) + ((fTemp28 + (1e+01f - fTemp31)) * ((((fRec1[(IOTA-int((int((int((iTemp30 + 1)) & 511)) + 1)))&1023] * (0 - (0.5f * fTemp32))) * (0 - (0.33333334f * fTemp34))) * (fTemp31 + (-8.0f - fTemp28))) + ((fTemp28 + (9.0f - fTemp31)) * (((0.5f * ((fRec1[(IOTA-int((int((int((iTemp30 + 2)) & 511)) + 1)))&1023] * (0 - (0.5f * fTemp34))) * (fTemp31 + (-7.0f - fTemp28)))) + (0.16666667f * ((fTemp33 * fRec1[(IOTA-int((int((int((iTemp30 + 3)) & 511)) + 1)))&1023]) * (fTemp31 + (-6.0f - fTemp28))))) + (0.041666668f * ((fTemp33 * fTemp32) * fRec1[(IOTA-int((int((int((iTemp30 + 4)) & 511)) + 1)))&1023])))))));
			fVec6[IOTA&65535] = fTemp35;
			float fTemp36 = ((float)input1[i] + (0.5f * (fTemp17 * ((fTemp16 * fVec6[(IOTA-iTemp15)&65535]) + (fRec6[0] * fVec6[(IOTA-iTemp14)&65535])))));
			float fTemp37 = cosf(fTemp19);
			float fTemp38 = (fTemp37 * fTemp36);
			float fTemp39 = (0 - fTemp20);
			float fTemp40 = ((fTemp39 * fRec10[1]) + fTemp38);
			int iTemp41 = itbl0[iSlow8];
			fRec16[0] = ((0.001f * iTemp41) + (0.999f * ((iTemp3 * iTemp41) + fRec16[1])));
			float fTemp42 = (fRec16[0] + -1.49999f);
			float fTemp43 = floorf(fTemp42);
			float fTemp44 = (fRec16[0] - fTemp43);
			float fTemp45 = (fTemp43 + (2.0f - fRec16[0]));
			float fTemp46 = (0 - (fTemp45 / fTemp44));
			float fTemp47 = ((fTemp39 * fRec14[1]) + (fTemp37 * fTemp40));
			int iTemp48 = itbl0[iSlow10];
			fRec20[0] = ((0.001f * iTemp48) + (0.999f * ((iTemp3 * iTemp48) + fRec20[1])));
			float fTemp49 = (fRec20[0] + -1.49999f);
			float fTemp50 = floorf(fTemp49);
			float fTemp51 = (fRec20[0] - fTemp50);
			float fTemp52 = (fTemp50 + (2.0f - fRec20[0]));
			float fTemp53 = (0 - (fTemp52 / fTemp51));
			float fTemp54 = ((fTemp39 * fRec18[1]) + (fTemp37 * fTemp47));
			int iTemp55 = itbl0[iSlow12];
			fRec24[0] = ((0.0001f * iTemp55) + (0.9999f * ((iTemp3 * iTemp55) + fRec24[1])));
			float fTemp56 = (fRec24[0] + -1.49999f);
			float fTemp57 = floorf(fTemp56);
			float fTemp58 = (fRec24[0] - fTemp57);
			float fTemp59 = (fTemp57 + (2.0f - fRec24[0]));
			float fTemp60 = (0 - (fTemp59 / fTemp58));
			float fTemp61 = ((fTemp39 * fRec22[1]) + (fTemp37 * fTemp54));
			float fTemp62 = (fTemp37 * fTemp18);
			float fTemp63 = ((fTemp39 * fRec9[1]) + fTemp62);
			float fTemp64 = ((fTemp39 * fRec13[1]) + (fTemp37 * fTemp63));
			float fTemp65 = ((fTemp39 * fRec17[1]) + (fTemp37 * fTemp64));
			float fTemp66 = ((fTemp39 * fRec21[1]) + (fTemp37 * fTemp65));
			float fTemp67 = ((6.123234e-17f * fTemp66) - fTemp61);
			fVec7[IOTA&16383] = fTemp67;
			int iTemp68 = int((int(fTemp56) & 8191));
			int iTemp69 = int((iTemp68 + 1));
			fRec23[0] = (((fTemp59 * fVec7[(IOTA-iTemp68)&16383]) / fTemp58) + (fVec7[(IOTA-iTemp69)&16383] + (fTemp60 * fRec23[1])));
			fRec21[0] = fRec23[0];
			int iTemp70 = itbl0[iSlow13];
			fRec26[0] = ((0.0001f * iTemp70) + (0.9999f * ((iTemp3 * iTemp70) + fRec26[1])));
			float fTemp71 = (fRec26[0] + -1.49999f);
			float fTemp72 = floorf(fTemp71);
			float fTemp73 = (fRec26[0] - fTemp72);
			float fTemp74 = (fTemp72 + (2.0f - fRec26[0]));
			float fTemp75 = (0 - (fTemp74 / fTemp73));
			float fTemp76 = (fTemp66 + (6.123234e-17f * fTemp61));
			fVec8[IOTA&16383] = fTemp76;
			int iTemp77 = int((int(fTemp71) & 8191));
			int iTemp78 = int((iTemp77 + 1));
			fRec25[0] = (((fTemp74 * fVec8[(IOTA-iTemp77)&16383]) / fTemp73) + (fVec8[(IOTA-iTemp78)&16383] + (fTemp75 * fRec25[1])));
			fRec22[0] = fRec25[0];
			float fTemp79 = ((fTemp37 * fRec22[1]) + (fTemp20 * fTemp54));
			float fTemp80 = ((fTemp37 * fRec21[1]) + (fTemp20 * fTemp65));
			float fTemp81 = ((6.123234e-17f * fTemp80) - fTemp79);
			fVec9[IOTA&16383] = fTemp81;
			int iTemp82 = int((int(fTemp49) & 8191));
			int iTemp83 = int((iTemp82 + 1));
			fRec19[0] = (((fTemp52 * fVec9[(IOTA-iTemp82)&16383]) / fTemp51) + (fVec9[(IOTA-iTemp83)&16383] + (fTemp53 * fRec19[1])));
			fRec17[0] = fRec19[0];
			int iTemp84 = itbl0[iSlow14];
			fRec28[0] = ((0.001f * iTemp84) + (0.999f * ((iTemp3 * iTemp84) + fRec28[1])));
			float fTemp85 = (fRec28[0] + -1.49999f);
			float fTemp86 = floorf(fTemp85);
			float fTemp87 = (fRec28[0] - fTemp86);
			float fTemp88 = (fTemp86 + (2.0f - fRec28[0]));
			float fTemp89 = (0 - (fTemp88 / fTemp87));
			float fTemp90 = (fTemp80 + (6.123234e-17f * fTemp79));
			fVec10[IOTA&16383] = fTemp90;
			int iTemp91 = int((int(fTemp85) & 8191));
			int iTemp92 = int((iTemp91 + 1));
			fRec27[0] = (((fTemp88 * fVec10[(IOTA-iTemp91)&16383]) / fTemp87) + (fVec10[(IOTA-iTemp92)&16383] + (fTemp89 * fRec27[1])));
			fRec18[0] = fRec27[0];
			float fTemp93 = ((fTemp37 * fRec18[1]) + (fTemp20 * fTemp47));
			float fTemp94 = ((fTemp37 * fRec17[1]) + (fTemp20 * fTemp64));
			float fTemp95 = ((6.123234e-17f * fTemp94) - fTemp93);
			fVec11[IOTA&16383] = fTemp95;
			int iTemp96 = int((int(fTemp42) & 8191));
			int iTemp97 = int((iTemp96 + 1));
			fRec15[0] = (((fTemp45 * fVec11[(IOTA-iTemp96)&16383]) / fTemp44) + (fVec11[(IOTA-iTemp97)&16383] + (fTemp46 * fRec15[1])));
			fRec13[0] = fRec15[0];
			int iTemp98 = itbl0[iSlow15];
			fRec30[0] = ((0.001f * iTemp98) + (0.999f * ((iTemp3 * iTemp98) + fRec30[1])));
			float fTemp99 = (fRec30[0] + -1.49999f);
			float fTemp100 = floorf(fTemp99);
			float fTemp101 = (fRec30[0] - fTemp100);
			float fTemp102 = (fTemp100 + (2.0f - fRec30[0]));
			float fTemp103 = (0 - (fTemp102 / fTemp101));
			float fTemp104 = (fTemp94 + (6.123234e-17f * fTemp93));
			fVec12[IOTA&16383] = fTemp104;
			int iTemp105 = int((int(fTemp99) & 8191));
			int iTemp106 = int((iTemp105 + 1));
			fRec29[0] = (((fTemp102 * fVec12[(IOTA-iTemp105)&16383]) / fTemp101) + (fVec12[(IOTA-iTemp106)&16383] + (fTemp103 * fRec29[1])));
			fRec14[0] = fRec29[0];
			float fTemp107 = ((fTemp37 * fRec14[1]) + (fTemp20 * fTemp40));
			float fTemp108 = ((fTemp37 * fRec13[1]) + (fTemp20 * fTemp63));
			float fTemp109 = ((6.123234e-17f * fTemp108) - fTemp107);
			fVec13[IOTA&16383] = fTemp109;
			int iTemp110 = int((int(fTemp23) & 8191));
			int iTemp111 = int((iTemp110 + 1));
			fRec11[0] = (((fTemp26 * fVec13[(IOTA-iTemp110)&16383]) / fTemp25) + (fVec13[(IOTA-iTemp111)&16383] + (fTemp27 * fRec11[1])));
			fRec9[0] = fRec11[0];
			int iTemp112 = itbl0[iSlow16];
			fRec32[0] = ((0.001f * iTemp112) + (0.999f * ((iTemp3 * iTemp112) + fRec32[1])));
			float fTemp113 = (fRec32[0] + -1.49999f);
			float fTemp114 = floorf(fTemp113);
			float fTemp115 = (fRec32[0] - fTemp114);
			float fTemp116 = (fTemp114 + (2.0f - fRec32[0]));
			float fTemp117 = (0 - (fTemp116 / fTemp115));
			float fTemp118 = (fTemp108 + (6.123234e-17f * fTemp107));
			fVec14[IOTA&16383] = fTemp118;
			int iTemp119 = int((int(fTemp113) & 8191));
			int iTemp120 = int((iTemp119 + 1));
			fRec31[0] = (((fTemp116 * fVec14[(IOTA-iTemp119)&16383]) / fTemp115) + (fVec14[(IOTA-iTemp120)&16383] + (fTemp117 * fRec31[1])));
			fRec10[0] = fRec31[0];
			float fTemp121 = ((fTemp37 * fRec9[1]) + fTemp21);
			float fTemp122 = (0 - fTemp19);
			float fTemp123 = sinf(fTemp122);
			int iTemp124 = itbl0[iSlow18];
			fRec36[0] = ((0.001f * iTemp124) + (0.999f * ((iTemp3 * iTemp124) + fRec36[1])));
			float fTemp125 = (fRec36[0] + -1.49999f);
			float fTemp126 = floorf(fTemp125);
			float fTemp127 = (fRec36[0] - fTemp126);
			float fTemp128 = (fTemp126 + (2.0f - fRec36[0]));
			float fTemp129 = (0 - (fTemp128 / fTemp127));
			float fTemp130 = (fTemp20 * fTemp36);
			float fTemp131 = ((fTemp39 * fRec38[1]) + fTemp38);
			float fTemp132 = ((fTemp39 * fRec41[1]) + (fTemp37 * fTemp131));
			float fTemp133 = ((fTemp39 * fRec44[1]) + (fTemp37 * fTemp132));
			float fTemp134 = ((fTemp39 * fRec47[1]) + (fTemp37 * fTemp133));
			float fTemp135 = ((fTemp39 * fRec37[1]) + fTemp62);
			float fTemp136 = ((fTemp39 * fRec40[1]) + (fTemp37 * fTemp135));
			float fTemp137 = ((fTemp39 * fRec43[1]) + (fTemp37 * fTemp136));
			float fTemp138 = ((fTemp39 * fRec46[1]) + (fTemp37 * fTemp137));
			float fTemp139 = ((6.123234e-17f * fTemp138) - fTemp134);
			fVec15[IOTA&16383] = fTemp139;
			fRec48[0] = (((fTemp59 * fVec15[(IOTA-iTemp68)&16383]) / fTemp58) + (fVec15[(IOTA-iTemp69)&16383] + (fTemp60 * fRec48[1])));
			fRec46[0] = fRec48[0];
			float fTemp140 = (fTemp138 + (6.123234e-17f * fTemp134));
			fVec16[IOTA&16383] = fTemp140;
			fRec49[0] = (((fTemp74 * fVec16[(IOTA-iTemp77)&16383]) / fTemp73) + (fVec16[(IOTA-iTemp78)&16383] + (fTemp75 * fRec49[1])));
			fRec47[0] = fRec49[0];
			float fTemp141 = ((fTemp37 * fRec47[1]) + (fTemp20 * fTemp133));
			float fTemp142 = ((fTemp37 * fRec46[1]) + (fTemp20 * fTemp137));
			float fTemp143 = ((6.123234e-17f * fTemp142) - fTemp141);
			fVec17[IOTA&16383] = fTemp143;
			fRec45[0] = (((fTemp52 * fVec17[(IOTA-iTemp82)&16383]) / fTemp51) + (fVec17[(IOTA-iTemp83)&16383] + (fTemp53 * fRec45[1])));
			fRec43[0] = fRec45[0];
			float fTemp144 = (fTemp142 + (6.123234e-17f * fTemp141));
			fVec18[IOTA&16383] = fTemp144;
			fRec50[0] = (((fTemp88 * fVec18[(IOTA-iTemp91)&16383]) / fTemp87) + (fVec18[(IOTA-iTemp92)&16383] + (fTemp89 * fRec50[1])));
			fRec44[0] = fRec50[0];
			float fTemp145 = ((fTemp37 * fRec44[1]) + (fTemp20 * fTemp132));
			float fTemp146 = ((fTemp37 * fRec43[1]) + (fTemp20 * fTemp136));
			float fTemp147 = ((6.123234e-17f * fTemp146) - fTemp145);
			fVec19[IOTA&16383] = fTemp147;
			fRec42[0] = (((fTemp45 * fVec19[(IOTA-iTemp96)&16383]) / fTemp44) + (fVec19[(IOTA-iTemp97)&16383] + (fTemp46 * fRec42[1])));
			fRec40[0] = fRec42[0];
			float fTemp148 = (fTemp146 + (6.123234e-17f * fTemp145));
			fVec20[IOTA&16383] = fTemp148;
			fRec51[0] = (((fTemp102 * fVec20[(IOTA-iTemp105)&16383]) / fTemp101) + (fVec20[(IOTA-iTemp106)&16383] + (fTemp103 * fRec51[1])));
			fRec41[0] = fRec51[0];
			float fTemp149 = ((fTemp37 * fRec41[1]) + (fTemp20 * fTemp131));
			float fTemp150 = ((fTemp37 * fRec40[1]) + (fTemp20 * fTemp135));
			float fTemp151 = ((6.123234e-17f * fTemp150) - fTemp149);
			fVec21[IOTA&16383] = fTemp151;
			fRec39[0] = (((fTemp26 * fVec21[(IOTA-iTemp110)&16383]) / fTemp25) + (fVec21[(IOTA-iTemp111)&16383] + (fTemp27 * fRec39[1])));
			fRec37[0] = fRec39[0];
			float fTemp152 = (fTemp150 + (6.123234e-17f * fTemp149));
			fVec22[IOTA&16383] = fTemp152;
			fRec52[0] = (((fTemp116 * fVec22[(IOTA-iTemp119)&16383]) / fTemp115) + (fVec22[(IOTA-iTemp120)&16383] + (fTemp117 * fRec52[1])));
			fRec38[0] = fRec52[0];
			float fTemp153 = ((fTemp37 * fRec38[1]) + fTemp130);
			float fTemp154 = cosf(fTemp122);
			float fTemp155 = (fTemp154 * fTemp153);
			float fTemp156 = (0 - fTemp123);
			float fTemp157 = (fTemp156 * fRec34[1]);
			int iTemp158 = itbl0[iSlow20];
			fRec56[0] = ((0.001f * iTemp158) + (0.999f * ((iTemp3 * iTemp158) + fRec56[1])));
			float fTemp159 = (fRec56[0] + -1.49999f);
			float fTemp160 = floorf(fTemp159);
			float fTemp161 = (fRec56[0] - fTemp160);
			float fTemp162 = (fTemp160 + (2.0f - fRec56[0]));
			float fTemp163 = (0 - (fTemp162 / fTemp161));
			float fTemp164 = ((fTemp39 * fRec58[1]) + fTemp38);
			float fTemp165 = ((fTemp39 * fRec61[1]) + (fTemp37 * fTemp164));
			float fTemp166 = ((fTemp39 * fRec64[1]) + (fTemp37 * fTemp165));
			float fTemp167 = ((fTemp39 * fRec67[1]) + (fTemp37 * fTemp166));
			float fTemp168 = ((fTemp39 * fRec57[1]) + fTemp62);
			float fTemp169 = ((fTemp39 * fRec60[1]) + (fTemp37 * fTemp168));
			float fTemp170 = ((fTemp39 * fRec63[1]) + (fTemp37 * fTemp169));
			float fTemp171 = ((fTemp39 * fRec66[1]) + (fTemp37 * fTemp170));
			float fTemp172 = ((6.123234e-17f * fTemp171) - fTemp167);
			fVec23[IOTA&16383] = fTemp172;
			fRec68[0] = (((fTemp59 * fVec23[(IOTA-iTemp68)&16383]) / fTemp58) + (fVec23[(IOTA-iTemp69)&16383] + (fTemp60 * fRec68[1])));
			fRec66[0] = fRec68[0];
			float fTemp173 = (fTemp171 + (6.123234e-17f * fTemp167));
			fVec24[IOTA&16383] = fTemp173;
			fRec69[0] = (((fTemp74 * fVec24[(IOTA-iTemp77)&16383]) / fTemp73) + (fVec24[(IOTA-iTemp78)&16383] + (fTemp75 * fRec69[1])));
			fRec67[0] = fRec69[0];
			float fTemp174 = ((fTemp37 * fRec67[1]) + (fTemp20 * fTemp166));
			float fTemp175 = ((fTemp37 * fRec66[1]) + (fTemp20 * fTemp170));
			float fTemp176 = ((6.123234e-17f * fTemp175) - fTemp174);
			fVec25[IOTA&16383] = fTemp176;
			fRec65[0] = (((fTemp52 * fVec25[(IOTA-iTemp82)&16383]) / fTemp51) + (fVec25[(IOTA-iTemp83)&16383] + (fTemp53 * fRec65[1])));
			fRec63[0] = fRec65[0];
			float fTemp177 = (fTemp175 + (6.123234e-17f * fTemp174));
			fVec26[IOTA&16383] = fTemp177;
			fRec70[0] = (((fTemp88 * fVec26[(IOTA-iTemp91)&16383]) / fTemp87) + (fVec26[(IOTA-iTemp92)&16383] + (fTemp89 * fRec70[1])));
			fRec64[0] = fRec70[0];
			float fTemp178 = ((fTemp37 * fRec64[1]) + (fTemp20 * fTemp165));
			float fTemp179 = ((fTemp37 * fRec63[1]) + (fTemp20 * fTemp169));
			float fTemp180 = ((6.123234e-17f * fTemp179) - fTemp178);
			fVec27[IOTA&16383] = fTemp180;
			fRec62[0] = (((fTemp45 * fVec27[(IOTA-iTemp96)&16383]) / fTemp44) + (fVec27[(IOTA-iTemp97)&16383] + (fTemp46 * fRec62[1])));
			fRec60[0] = fRec62[0];
			float fTemp181 = (fTemp179 + (6.123234e-17f * fTemp178));
			fVec28[IOTA&16383] = fTemp181;
			fRec71[0] = (((fTemp102 * fVec28[(IOTA-iTemp105)&16383]) / fTemp101) + (fVec28[(IOTA-iTemp106)&16383] + (fTemp103 * fRec71[1])));
			fRec61[0] = fRec71[0];
			float fTemp182 = ((fTemp37 * fRec61[1]) + (fTemp20 * fTemp164));
			float fTemp183 = ((fTemp37 * fRec60[1]) + (fTemp20 * fTemp168));
			float fTemp184 = ((6.123234e-17f * fTemp183) - fTemp182);
			fVec29[IOTA&16383] = fTemp184;
			fRec59[0] = (((fTemp26 * fVec29[(IOTA-iTemp110)&16383]) / fTemp25) + (fVec29[(IOTA-iTemp111)&16383] + (fTemp27 * fRec59[1])));
			fRec57[0] = fRec59[0];
			float fTemp185 = (fTemp183 + (6.123234e-17f * fTemp182));
			fVec30[IOTA&16383] = fTemp185;
			fRec72[0] = (((fTemp116 * fVec30[(IOTA-iTemp119)&16383]) / fTemp115) + (fVec30[(IOTA-iTemp120)&16383] + (fTemp117 * fRec72[1])));
			fRec58[0] = fRec72[0];
			float fTemp186 = ((fTemp37 * fRec58[1]) + fTemp130);
			float fTemp187 = (fTemp154 * fTemp186);
			float fTemp188 = (fTemp156 * fRec54[1]);
			float fTemp189 = (fTemp188 + (fTemp154 * (fTemp157 + fTemp187)));
			int iTemp190 = itbl0[iSlow22];
			fRec76[0] = ((0.001f * iTemp190) + (0.999f * ((iTemp3 * iTemp190) + fRec76[1])));
			float fTemp191 = (fRec76[0] + -1.49999f);
			float fTemp192 = floorf(fTemp191);
			float fTemp193 = (fRec76[0] - fTemp192);
			float fTemp194 = (fTemp192 + (2.0f - fRec76[0]));
			float fTemp195 = (0 - (fTemp194 / fTemp193));
			float fTemp196 = (fTemp156 * fRec74[1]);
			int iTemp197 = itbl0[iSlow24];
			fRec80[0] = ((0.0001f * iTemp197) + (0.9999f * ((iTemp3 * iTemp197) + fRec80[1])));
			float fTemp198 = (fRec80[0] + -1.49999f);
			float fTemp199 = floorf(fTemp198);
			float fTemp200 = (fRec80[0] - fTemp199);
			float fTemp201 = (fTemp199 + (2.0f - fRec80[0]));
			float fTemp202 = (0 - (fTemp201 / fTemp200));
			float fTemp203 = ((fTemp39 * fRec82[1]) + fTemp38);
			float fTemp204 = ((fTemp39 * fRec85[1]) + (fTemp37 * fTemp203));
			float fTemp205 = ((fTemp39 * fRec88[1]) + (fTemp37 * fTemp204));
			float fTemp206 = ((fTemp39 * fRec91[1]) + (fTemp37 * fTemp205));
			float fTemp207 = ((fTemp39 * fRec81[1]) + fTemp62);
			float fTemp208 = ((fTemp39 * fRec84[1]) + (fTemp37 * fTemp207));
			float fTemp209 = ((fTemp39 * fRec87[1]) + (fTemp37 * fTemp208));
			float fTemp210 = ((fTemp39 * fRec90[1]) + (fTemp37 * fTemp209));
			float fTemp211 = ((6.123234e-17f * fTemp210) - fTemp206);
			fVec31[IOTA&16383] = fTemp211;
			fRec92[0] = (((fTemp59 * fVec31[(IOTA-iTemp68)&16383]) / fTemp58) + (fVec31[(IOTA-iTemp69)&16383] + (fTemp60 * fRec92[1])));
			fRec90[0] = fRec92[0];
			float fTemp212 = (fTemp210 + (6.123234e-17f * fTemp206));
			fVec32[IOTA&16383] = fTemp212;
			fRec93[0] = (((fTemp74 * fVec32[(IOTA-iTemp77)&16383]) / fTemp73) + (fVec32[(IOTA-iTemp78)&16383] + (fTemp75 * fRec93[1])));
			fRec91[0] = fRec93[0];
			float fTemp213 = ((fTemp37 * fRec91[1]) + (fTemp20 * fTemp205));
			float fTemp214 = ((fTemp37 * fRec90[1]) + (fTemp20 * fTemp209));
			float fTemp215 = ((6.123234e-17f * fTemp214) - fTemp213);
			fVec33[IOTA&16383] = fTemp215;
			fRec89[0] = (((fTemp52 * fVec33[(IOTA-iTemp82)&16383]) / fTemp51) + (fVec33[(IOTA-iTemp83)&16383] + (fTemp53 * fRec89[1])));
			fRec87[0] = fRec89[0];
			float fTemp216 = (fTemp214 + (6.123234e-17f * fTemp213));
			fVec34[IOTA&16383] = fTemp216;
			fRec94[0] = (((fTemp88 * fVec34[(IOTA-iTemp91)&16383]) / fTemp87) + (fVec34[(IOTA-iTemp92)&16383] + (fTemp89 * fRec94[1])));
			fRec88[0] = fRec94[0];
			float fTemp217 = ((fTemp37 * fRec88[1]) + (fTemp20 * fTemp204));
			float fTemp218 = ((fTemp37 * fRec87[1]) + (fTemp20 * fTemp208));
			float fTemp219 = ((6.123234e-17f * fTemp218) - fTemp217);
			fVec35[IOTA&16383] = fTemp219;
			fRec86[0] = (((fTemp45 * fVec35[(IOTA-iTemp96)&16383]) / fTemp44) + (fVec35[(IOTA-iTemp97)&16383] + (fTemp46 * fRec86[1])));
			fRec84[0] = fRec86[0];
			float fTemp220 = (fTemp218 + (6.123234e-17f * fTemp217));
			fVec36[IOTA&16383] = fTemp220;
			fRec95[0] = (((fTemp102 * fVec36[(IOTA-iTemp105)&16383]) / fTemp101) + (fVec36[(IOTA-iTemp106)&16383] + (fTemp103 * fRec95[1])));
			fRec85[0] = fRec95[0];
			float fTemp221 = ((fTemp37 * fRec85[1]) + (fTemp20 * fTemp203));
			float fTemp222 = ((fTemp37 * fRec84[1]) + (fTemp20 * fTemp207));
			float fTemp223 = ((6.123234e-17f * fTemp222) - fTemp221);
			fVec37[IOTA&16383] = fTemp223;
			fRec83[0] = (((fTemp26 * fVec37[(IOTA-iTemp110)&16383]) / fTemp25) + (fVec37[(IOTA-iTemp111)&16383] + (fTemp27 * fRec83[1])));
			fRec81[0] = fRec83[0];
			float fTemp224 = (fTemp222 + (6.123234e-17f * fTemp221));
			fVec38[IOTA&16383] = fTemp224;
			fRec96[0] = (((fTemp116 * fVec38[(IOTA-iTemp119)&16383]) / fTemp115) + (fVec38[(IOTA-iTemp120)&16383] + (fTemp117 * fRec96[1])));
			fRec82[0] = fRec96[0];
			float fTemp225 = ((fTemp37 * fRec82[1]) + fTemp130);
			float fTemp226 = (fTemp154 * fTemp225);
			float fTemp227 = ((fTemp156 * fRec78[1]) + (fTemp154 * (fTemp196 + (fTemp154 * (fTemp188 + (fTemp154 * (fTemp157 + fTemp226)))))));
			float fTemp228 = (fTemp156 * fRec33[1]);
			float fTemp229 = ((fTemp37 * fRec81[1]) + fTemp21);
			float fTemp230 = (fTemp154 * fTemp229);
			float fTemp231 = (fTemp156 * fRec53[1]);
			float fTemp232 = (fTemp156 * fRec73[1]);
			float fTemp233 = ((fTemp156 * fRec77[1]) + (fTemp154 * (fTemp232 + (fTemp154 * (fTemp231 + (fTemp154 * (fTemp230 + fTemp228)))))));
			float fTemp234 = ((6.123234e-17f * fTemp233) - fTemp227);
			fVec39[IOTA&16383] = fTemp234;
			int iTemp235 = int((int(fTemp198) & 8191));
			int iTemp236 = int((iTemp235 + 1));
			fRec79[0] = (((fTemp201 * fVec39[(IOTA-iTemp235)&16383]) / fTemp200) + (fVec39[(IOTA-iTemp236)&16383] + (fTemp202 * fRec79[1])));
			fRec77[0] = fRec79[0];
			int iTemp237 = itbl0[iSlow25];
			fRec98[0] = ((0.0001f * iTemp237) + (0.9999f * ((iTemp3 * iTemp237) + fRec98[1])));
			float fTemp238 = (fRec98[0] + -1.49999f);
			float fTemp239 = floorf(fTemp238);
			float fTemp240 = (fRec98[0] - fTemp239);
			float fTemp241 = (fTemp239 + (2.0f - fRec98[0]));
			float fTemp242 = (0 - (fTemp241 / fTemp240));
			float fTemp243 = (fTemp233 + (6.123234e-17f * fTemp227));
			fVec40[IOTA&16383] = fTemp243;
			int iTemp244 = int((int(fTemp238) & 8191));
			int iTemp245 = int((iTemp244 + 1));
			fRec97[0] = (((fTemp241 * fVec40[(IOTA-iTemp244)&16383]) / fTemp240) + (fVec40[(IOTA-iTemp245)&16383] + (fTemp242 * fRec97[1])));
			fRec78[0] = fRec97[0];
			float fTemp246 = ((fTemp154 * fRec78[1]) + (fTemp123 * (fTemp196 + (fTemp154 * fTemp189))));
			float fTemp247 = ((fTemp37 * fRec57[1]) + fTemp21);
			float fTemp248 = (fTemp154 * fTemp247);
			float fTemp249 = (fTemp231 + (fTemp154 * (fTemp248 + fTemp228)));
			float fTemp250 = ((fTemp154 * fRec77[1]) + (fTemp123 * (fTemp232 + (fTemp154 * fTemp249))));
			float fTemp251 = ((6.123234e-17f * fTemp250) - fTemp246);
			fVec41[IOTA&16383] = fTemp251;
			int iTemp252 = int((int(fTemp191) & 8191));
			int iTemp253 = int((iTemp252 + 1));
			fRec75[0] = (((fTemp194 * fVec41[(IOTA-iTemp252)&16383]) / fTemp193) + (fVec41[(IOTA-iTemp253)&16383] + (fTemp195 * fRec75[1])));
			fRec73[0] = fRec75[0];
			int iTemp254 = itbl0[iSlow26];
			fRec100[0] = ((0.001f * iTemp254) + (0.999f * ((iTemp3 * iTemp254) + fRec100[1])));
			float fTemp255 = (fRec100[0] + -1.49999f);
			float fTemp256 = floorf(fTemp255);
			float fTemp257 = (fRec100[0] - fTemp256);
			float fTemp258 = (fTemp256 + (2.0f - fRec100[0]));
			float fTemp259 = (0 - (fTemp258 / fTemp257));
			float fTemp260 = (fTemp250 + (6.123234e-17f * fTemp246));
			fVec42[IOTA&16383] = fTemp260;
			int iTemp261 = int((int(fTemp255) & 8191));
			int iTemp262 = int((iTemp261 + 1));
			fRec99[0] = (((fTemp258 * fVec42[(IOTA-iTemp261)&16383]) / fTemp257) + (fVec42[(IOTA-iTemp262)&16383] + (fTemp259 * fRec99[1])));
			fRec74[0] = fRec99[0];
			float fTemp263 = ((fTemp154 * fRec74[1]) + (fTemp123 * fTemp189));
			float fTemp264 = ((fTemp154 * fRec73[1]) + (fTemp123 * fTemp249));
			float fTemp265 = ((6.123234e-17f * fTemp264) - fTemp263);
			fVec43[IOTA&16383] = fTemp265;
			int iTemp266 = int((int(fTemp159) & 8191));
			int iTemp267 = int((iTemp266 + 1));
			fRec55[0] = (((fTemp162 * fVec43[(IOTA-iTemp266)&16383]) / fTemp161) + (fVec43[(IOTA-iTemp267)&16383] + (fTemp163 * fRec55[1])));
			fRec53[0] = fRec55[0];
			int iTemp268 = itbl0[iSlow27];
			fRec102[0] = ((0.001f * iTemp268) + (0.999f * ((iTemp3 * iTemp268) + fRec102[1])));
			float fTemp269 = (fRec102[0] + -1.49999f);
			float fTemp270 = floorf(fTemp269);
			float fTemp271 = (fRec102[0] - fTemp270);
			float fTemp272 = (fTemp270 + (2.0f - fRec102[0]));
			float fTemp273 = (0 - (fTemp272 / fTemp271));
			float fTemp274 = (fTemp264 + (6.123234e-17f * fTemp263));
			fVec44[IOTA&16383] = fTemp274;
			int iTemp275 = int((int(fTemp269) & 8191));
			int iTemp276 = int((iTemp275 + 1));
			fRec101[0] = (((fTemp272 * fVec44[(IOTA-iTemp275)&16383]) / fTemp271) + (fVec44[(IOTA-iTemp276)&16383] + (fTemp273 * fRec101[1])));
			fRec54[0] = fRec101[0];
			float fTemp277 = ((fTemp154 * fRec54[1]) + (fTemp123 * (fTemp157 + fTemp155)));
			float fTemp278 = ((fTemp37 * fRec37[1]) + fTemp21);
			float fTemp279 = (fTemp154 * fTemp278);
			float fTemp280 = ((fTemp154 * fRec53[1]) + (fTemp123 * (fTemp279 + fTemp228)));
			float fTemp281 = ((6.123234e-17f * fTemp280) - fTemp277);
			fVec45[IOTA&16383] = fTemp281;
			int iTemp282 = int((int(fTemp125) & 8191));
			int iTemp283 = int((iTemp282 + 1));
			fRec35[0] = (((fTemp128 * fVec45[(IOTA-iTemp282)&16383]) / fTemp127) + (fVec45[(IOTA-iTemp283)&16383] + (fTemp129 * fRec35[1])));
			fRec33[0] = fRec35[0];
			int iTemp284 = itbl0[iSlow28];
			fRec104[0] = ((0.001f * iTemp284) + (0.999f * ((iTemp3 * iTemp284) + fRec104[1])));
			float fTemp285 = (fRec104[0] + -1.49999f);
			float fTemp286 = floorf(fTemp285);
			float fTemp287 = (fRec104[0] - fTemp286);
			float fTemp288 = (fTemp286 + (2.0f - fRec104[0]));
			float fTemp289 = (0 - (fTemp288 / fTemp287));
			float fTemp290 = (fTemp280 + (6.123234e-17f * fTemp277));
			fVec46[IOTA&16383] = fTemp290;
			int iTemp291 = int((int(fTemp285) & 8191));
			int iTemp292 = int((iTemp291 + 1));
			fRec103[0] = (((fTemp288 * fVec46[(IOTA-iTemp291)&16383]) / fTemp287) + (fVec46[(IOTA-iTemp292)&16383] + (fTemp289 * fRec103[1])));
			fRec34[0] = fRec103[0];
			float fTemp293 = (fTemp156 * fRec109[1]);
			float fTemp294 = (fTemp293 + fTemp187);
			float fTemp295 = (fTemp156 * fRec112[1]);
			float fTemp296 = (fTemp156 * fRec115[1]);
			float fTemp297 = ((fTemp39 * fRec121[1]) + fTemp38);
			float fTemp298 = ((fTemp39 * fRec124[1]) + (fTemp37 * fTemp297));
			float fTemp299 = ((fTemp39 * fRec127[1]) + (fTemp37 * fTemp298));
			float fTemp300 = ((fTemp39 * fRec130[1]) + (fTemp37 * fTemp299));
			float fTemp301 = ((fTemp39 * fRec120[1]) + fTemp62);
			float fTemp302 = ((fTemp39 * fRec123[1]) + (fTemp37 * fTemp301));
			float fTemp303 = ((fTemp39 * fRec126[1]) + (fTemp37 * fTemp302));
			float fTemp304 = ((fTemp39 * fRec129[1]) + (fTemp37 * fTemp303));
			float fTemp305 = ((6.123234e-17f * fTemp304) - fTemp300);
			fVec47[IOTA&16383] = fTemp305;
			fRec131[0] = (((fTemp59 * fVec47[(IOTA-iTemp68)&16383]) / fTemp58) + (fVec47[(IOTA-iTemp69)&16383] + (fTemp60 * fRec131[1])));
			fRec129[0] = fRec131[0];
			float fTemp306 = (fTemp304 + (6.123234e-17f * fTemp300));
			fVec48[IOTA&16383] = fTemp306;
			fRec132[0] = (((fTemp74 * fVec48[(IOTA-iTemp77)&16383]) / fTemp73) + (fVec48[(IOTA-iTemp78)&16383] + (fTemp75 * fRec132[1])));
			fRec130[0] = fRec132[0];
			float fTemp307 = ((fTemp37 * fRec130[1]) + (fTemp20 * fTemp299));
			float fTemp308 = ((fTemp37 * fRec129[1]) + (fTemp20 * fTemp303));
			float fTemp309 = ((6.123234e-17f * fTemp308) - fTemp307);
			fVec49[IOTA&16383] = fTemp309;
			fRec128[0] = (((fTemp52 * fVec49[(IOTA-iTemp82)&16383]) / fTemp51) + (fVec49[(IOTA-iTemp83)&16383] + (fTemp53 * fRec128[1])));
			fRec126[0] = fRec128[0];
			float fTemp310 = (fTemp308 + (6.123234e-17f * fTemp307));
			fVec50[IOTA&16383] = fTemp310;
			fRec133[0] = (((fTemp88 * fVec50[(IOTA-iTemp91)&16383]) / fTemp87) + (fVec50[(IOTA-iTemp92)&16383] + (fTemp89 * fRec133[1])));
			fRec127[0] = fRec133[0];
			float fTemp311 = ((fTemp37 * fRec127[1]) + (fTemp20 * fTemp298));
			float fTemp312 = ((fTemp37 * fRec126[1]) + (fTemp20 * fTemp302));
			float fTemp313 = ((6.123234e-17f * fTemp312) - fTemp311);
			fVec51[IOTA&16383] = fTemp313;
			fRec125[0] = (((fTemp45 * fVec51[(IOTA-iTemp96)&16383]) / fTemp44) + (fVec51[(IOTA-iTemp97)&16383] + (fTemp46 * fRec125[1])));
			fRec123[0] = fRec125[0];
			float fTemp314 = (fTemp312 + (6.123234e-17f * fTemp311));
			fVec52[IOTA&16383] = fTemp314;
			fRec134[0] = (((fTemp102 * fVec52[(IOTA-iTemp105)&16383]) / fTemp101) + (fVec52[(IOTA-iTemp106)&16383] + (fTemp103 * fRec134[1])));
			fRec124[0] = fRec134[0];
			float fTemp315 = ((fTemp37 * fRec124[1]) + (fTemp20 * fTemp297));
			float fTemp316 = ((fTemp37 * fRec123[1]) + (fTemp20 * fTemp301));
			float fTemp317 = ((6.123234e-17f * fTemp316) - fTemp315);
			fVec53[IOTA&16383] = fTemp317;
			fRec122[0] = (((fTemp26 * fVec53[(IOTA-iTemp110)&16383]) / fTemp25) + (fVec53[(IOTA-iTemp111)&16383] + (fTemp27 * fRec122[1])));
			fRec120[0] = fRec122[0];
			float fTemp318 = (fTemp316 + (6.123234e-17f * fTemp315));
			fVec54[IOTA&16383] = fTemp318;
			fRec135[0] = (((fTemp116 * fVec54[(IOTA-iTemp119)&16383]) / fTemp115) + (fVec54[(IOTA-iTemp120)&16383] + (fTemp117 * fRec135[1])));
			fRec121[0] = fRec135[0];
			float fTemp319 = (fTemp154 * ((fTemp37 * fRec121[1]) + fTemp130));
			float fTemp320 = ((fTemp156 * fRec118[1]) + (fTemp154 * (fTemp296 + (fTemp154 * (fTemp295 + (fTemp154 * (fTemp293 + fTemp319)))))));
			float fTemp321 = (fTemp156 * fRec108[1]);
			float fTemp322 = (fTemp154 * ((fTemp37 * fRec120[1]) + fTemp21));
			float fTemp323 = (fTemp156 * fRec111[1]);
			float fTemp324 = (fTemp156 * fRec114[1]);
			float fTemp325 = ((fTemp156 * fRec117[1]) + (fTemp154 * (fTemp324 + (fTemp154 * (fTemp323 + (fTemp154 * (fTemp322 + fTemp321)))))));
			float fTemp326 = ((6.123234e-17f * fTemp325) - fTemp320);
			fVec55[IOTA&16383] = fTemp326;
			fRec119[0] = (((fTemp201 * fVec55[(IOTA-iTemp235)&16383]) / fTemp200) + (fVec55[(IOTA-iTemp236)&16383] + (fTemp202 * fRec119[1])));
			fRec117[0] = fRec119[0];
			float fTemp327 = (fTemp325 + (6.123234e-17f * fTemp320));
			fVec56[IOTA&16383] = fTemp327;
			fRec136[0] = (((fTemp241 * fVec56[(IOTA-iTemp244)&16383]) / fTemp240) + (fVec56[(IOTA-iTemp245)&16383] + (fTemp242 * fRec136[1])));
			fRec118[0] = fRec136[0];
			float fTemp328 = ((fTemp154 * fRec118[1]) + (fTemp123 * (fTemp296 + (fTemp154 * (fTemp295 + (fTemp154 * (fTemp293 + fTemp226)))))));
			float fTemp329 = ((fTemp154 * fRec117[1]) + (fTemp123 * (fTemp324 + (fTemp154 * (fTemp323 + (fTemp154 * (fTemp230 + fTemp321)))))));
			float fTemp330 = ((6.123234e-17f * fTemp329) - fTemp328);
			fVec57[IOTA&16383] = fTemp330;
			fRec116[0] = (((fTemp194 * fVec57[(IOTA-iTemp252)&16383]) / fTemp193) + (fVec57[(IOTA-iTemp253)&16383] + (fTemp195 * fRec116[1])));
			fRec114[0] = fRec116[0];
			float fTemp331 = (fTemp329 + (6.123234e-17f * fTemp328));
			fVec58[IOTA&16383] = fTemp331;
			fRec137[0] = (((fTemp258 * fVec58[(IOTA-iTemp261)&16383]) / fTemp257) + (fVec58[(IOTA-iTemp262)&16383] + (fTemp259 * fRec137[1])));
			fRec115[0] = fRec137[0];
			float fTemp332 = ((fTemp154 * fRec115[1]) + (fTemp123 * (fTemp295 + (fTemp154 * fTemp294))));
			float fTemp333 = (fTemp248 + fTemp321);
			float fTemp334 = ((fTemp154 * fRec114[1]) + (fTemp123 * (fTemp323 + (fTemp154 * fTemp333))));
			float fTemp335 = ((6.123234e-17f * fTemp334) - fTemp332);
			fVec59[IOTA&16383] = fTemp335;
			fRec113[0] = (((fTemp162 * fVec59[(IOTA-iTemp266)&16383]) / fTemp161) + (fVec59[(IOTA-iTemp267)&16383] + (fTemp163 * fRec113[1])));
			fRec111[0] = fRec113[0];
			float fTemp336 = (fTemp334 + (6.123234e-17f * fTemp332));
			fVec60[IOTA&16383] = fTemp336;
			fRec138[0] = (((fTemp272 * fVec60[(IOTA-iTemp275)&16383]) / fTemp271) + (fVec60[(IOTA-iTemp276)&16383] + (fTemp273 * fRec138[1])));
			fRec112[0] = fRec138[0];
			float fTemp337 = ((fTemp154 * fRec112[1]) + (fTemp123 * fTemp294));
			float fTemp338 = ((fTemp154 * fRec111[1]) + (fTemp123 * fTemp333));
			float fTemp339 = ((6.123234e-17f * fTemp338) - fTemp337);
			fVec61[IOTA&16383] = fTemp339;
			fRec110[0] = (((fTemp128 * fVec61[(IOTA-iTemp282)&16383]) / fTemp127) + (fVec61[(IOTA-iTemp283)&16383] + (fTemp129 * fRec110[1])));
			fRec108[0] = fRec110[0];
			float fTemp340 = (fTemp338 + (6.123234e-17f * fTemp337));
			fVec62[IOTA&16383] = fTemp340;
			fRec139[0] = (((fTemp288 * fVec62[(IOTA-iTemp291)&16383]) / fTemp287) + (fVec62[(IOTA-iTemp292)&16383] + (fTemp289 * fRec139[1])));
			fRec109[0] = fRec139[0];
			float fTemp341 = (fTemp39 * fRec106[1]);
			float fTemp342 = (fTemp123 * fTemp186);
			float fTemp343 = (fTemp156 * fRec144[1]);
			float fTemp344 = (fTemp156 * fRec147[1]);
			float fTemp345 = (fTemp156 * fRec150[1]);
			float fTemp346 = ((fTemp37 * fRec10[1]) + fTemp130);
			float fTemp347 = (fTemp154 * fTemp346);
			float fTemp348 = ((fTemp156 * fRec153[1]) + (fTemp154 * (fTemp345 + (fTemp154 * (fTemp344 + (fTemp154 * (fTemp343 + fTemp347)))))));
			float fTemp349 = (fTemp156 * fRec143[1]);
			float fTemp350 = (fTemp154 * fTemp121);
			float fTemp351 = (fTemp156 * fRec146[1]);
			float fTemp352 = (fTemp156 * fRec149[1]);
			float fTemp353 = ((fTemp156 * fRec152[1]) + (fTemp154 * (fTemp352 + (fTemp154 * (fTemp351 + (fTemp154 * (fTemp350 + fTemp349)))))));
			float fTemp354 = ((6.123234e-17f * fTemp353) - fTemp348);
			fVec63[IOTA&16383] = fTemp354;
			fRec154[0] = (((fTemp201 * fVec63[(IOTA-iTemp235)&16383]) / fTemp200) + (fVec63[(IOTA-iTemp236)&16383] + (fTemp202 * fRec154[1])));
			fRec152[0] = fRec154[0];
			float fTemp355 = (fTemp353 + (6.123234e-17f * fTemp348));
			fVec64[IOTA&16383] = fTemp355;
			fRec155[0] = (((fTemp241 * fVec64[(IOTA-iTemp244)&16383]) / fTemp240) + (fVec64[(IOTA-iTemp245)&16383] + (fTemp242 * fRec155[1])));
			fRec153[0] = fRec155[0];
			float fTemp356 = ((fTemp154 * fRec153[1]) + (fTemp123 * (fTemp345 + (fTemp154 * (fTemp344 + (fTemp154 * (fTemp343 + fTemp319)))))));
			float fTemp357 = ((fTemp154 * fRec152[1]) + (fTemp123 * (fTemp352 + (fTemp154 * (fTemp351 + (fTemp154 * (fTemp322 + fTemp349)))))));
			float fTemp358 = ((6.123234e-17f * fTemp357) - fTemp356);
			fVec65[IOTA&16383] = fTemp358;
			fRec151[0] = (((fTemp194 * fVec65[(IOTA-iTemp252)&16383]) / fTemp193) + (fVec65[(IOTA-iTemp253)&16383] + (fTemp195 * fRec151[1])));
			fRec149[0] = fRec151[0];
			float fTemp359 = (fTemp357 + (6.123234e-17f * fTemp356));
			fVec66[IOTA&16383] = fTemp359;
			fRec156[0] = (((fTemp258 * fVec66[(IOTA-iTemp261)&16383]) / fTemp257) + (fVec66[(IOTA-iTemp262)&16383] + (fTemp259 * fRec156[1])));
			fRec150[0] = fRec156[0];
			float fTemp360 = ((fTemp154 * fRec150[1]) + (fTemp123 * (fTemp344 + (fTemp154 * (fTemp343 + fTemp226)))));
			float fTemp361 = ((fTemp154 * fRec149[1]) + (fTemp123 * (fTemp351 + (fTemp154 * (fTemp230 + fTemp349)))));
			float fTemp362 = ((6.123234e-17f * fTemp361) - fTemp360);
			fVec67[IOTA&16383] = fTemp362;
			fRec148[0] = (((fTemp162 * fVec67[(IOTA-iTemp266)&16383]) / fTemp161) + (fVec67[(IOTA-iTemp267)&16383] + (fTemp163 * fRec148[1])));
			fRec146[0] = fRec148[0];
			float fTemp363 = (fTemp361 + (6.123234e-17f * fTemp360));
			fVec68[IOTA&16383] = fTemp363;
			fRec157[0] = (((fTemp272 * fVec68[(IOTA-iTemp275)&16383]) / fTemp271) + (fVec68[(IOTA-iTemp276)&16383] + (fTemp273 * fRec157[1])));
			fRec147[0] = fRec157[0];
			float fTemp364 = ((fTemp154 * fRec147[1]) + (fTemp123 * (fTemp343 + fTemp187)));
			float fTemp365 = ((fTemp154 * fRec146[1]) + (fTemp123 * (fTemp349 + fTemp248)));
			float fTemp366 = ((6.123234e-17f * fTemp365) - fTemp364);
			fVec69[IOTA&16383] = fTemp366;
			fRec145[0] = (((fTemp128 * fVec69[(IOTA-iTemp282)&16383]) / fTemp127) + (fVec69[(IOTA-iTemp283)&16383] + (fTemp129 * fRec145[1])));
			fRec143[0] = fRec145[0];
			float fTemp367 = (fTemp365 + (6.123234e-17f * fTemp364));
			fVec70[IOTA&16383] = fTemp367;
			fRec158[0] = (((fTemp288 * fVec70[(IOTA-iTemp291)&16383]) / fTemp287) + (fVec70[(IOTA-iTemp292)&16383] + (fTemp289 * fRec158[1])));
			fRec144[0] = fRec158[0];
			float fTemp368 = (fTemp39 * fRec141[1]);
			float fTemp369 = (fTemp156 * fRec163[1]);
			float fTemp370 = (fTemp156 * fRec166[1]);
			float fTemp371 = (fTemp156 * fRec169[1]);
			float fTemp372 = ((fTemp156 * fRec172[1]) + (fTemp154 * (fTemp371 + (fTemp154 * (fTemp370 + (fTemp154 * (fTemp369 + fTemp155)))))));
			float fTemp373 = (fTemp156 * fRec162[1]);
			float fTemp374 = (fTemp156 * fRec165[1]);
			float fTemp375 = (fTemp156 * fRec168[1]);
			float fTemp376 = ((fTemp156 * fRec171[1]) + (fTemp154 * (fTemp375 + (fTemp154 * (fTemp374 + (fTemp154 * (fTemp279 + fTemp373)))))));
			float fTemp377 = ((6.123234e-17f * fTemp376) - fTemp372);
			fVec71[IOTA&16383] = fTemp377;
			fRec173[0] = (((fTemp201 * fVec71[(IOTA-iTemp235)&16383]) / fTemp200) + (fVec71[(IOTA-iTemp236)&16383] + (fTemp202 * fRec173[1])));
			fRec171[0] = fRec173[0];
			float fTemp378 = (fTemp376 + (6.123234e-17f * fTemp372));
			fVec72[IOTA&16383] = fTemp378;
			fRec174[0] = (((fTemp241 * fVec72[(IOTA-iTemp244)&16383]) / fTemp240) + (fVec72[(IOTA-iTemp245)&16383] + (fTemp242 * fRec174[1])));
			fRec172[0] = fRec174[0];
			float fTemp379 = ((fTemp154 * fRec172[1]) + (fTemp123 * (fTemp371 + (fTemp154 * (fTemp370 + (fTemp154 * (fTemp369 + fTemp347)))))));
			float fTemp380 = ((fTemp154 * fRec171[1]) + (fTemp123 * (fTemp375 + (fTemp154 * (fTemp374 + (fTemp154 * (fTemp350 + fTemp373)))))));
			float fTemp381 = ((6.123234e-17f * fTemp380) - fTemp379);
			fVec73[IOTA&16383] = fTemp381;
			fRec170[0] = (((fTemp194 * fVec73[(IOTA-iTemp252)&16383]) / fTemp193) + (fVec73[(IOTA-iTemp253)&16383] + (fTemp195 * fRec170[1])));
			fRec168[0] = fRec170[0];
			float fTemp382 = (fTemp380 + (6.123234e-17f * fTemp379));
			fVec74[IOTA&16383] = fTemp382;
			fRec175[0] = (((fTemp258 * fVec74[(IOTA-iTemp261)&16383]) / fTemp257) + (fVec74[(IOTA-iTemp262)&16383] + (fTemp259 * fRec175[1])));
			fRec169[0] = fRec175[0];
			float fTemp383 = ((fTemp154 * fRec169[1]) + (fTemp123 * (fTemp370 + (fTemp154 * (fTemp369 + fTemp319)))));
			float fTemp384 = ((fTemp154 * fRec168[1]) + (fTemp123 * (fTemp374 + (fTemp154 * (fTemp322 + fTemp373)))));
			float fTemp385 = ((6.123234e-17f * fTemp384) - fTemp383);
			fVec75[IOTA&16383] = fTemp385;
			fRec167[0] = (((fTemp162 * fVec75[(IOTA-iTemp266)&16383]) / fTemp161) + (fVec75[(IOTA-iTemp267)&16383] + (fTemp163 * fRec167[1])));
			fRec165[0] = fRec167[0];
			float fTemp386 = (fTemp384 + (6.123234e-17f * fTemp383));
			fVec76[IOTA&16383] = fTemp386;
			fRec176[0] = (((fTemp272 * fVec76[(IOTA-iTemp275)&16383]) / fTemp271) + (fVec76[(IOTA-iTemp276)&16383] + (fTemp273 * fRec176[1])));
			fRec166[0] = fRec176[0];
			float fTemp387 = ((fTemp154 * fRec166[1]) + (fTemp123 * (fTemp369 + fTemp226)));
			float fTemp388 = ((fTemp154 * fRec165[1]) + (fTemp123 * (fTemp373 + fTemp230)));
			float fTemp389 = ((6.123234e-17f * fTemp388) - fTemp387);
			fVec77[IOTA&16383] = fTemp389;
			fRec164[0] = (((fTemp128 * fVec77[(IOTA-iTemp282)&16383]) / fTemp127) + (fVec77[(IOTA-iTemp283)&16383] + (fTemp129 * fRec164[1])));
			fRec162[0] = fRec164[0];
			float fTemp390 = (fTemp388 + (6.123234e-17f * fTemp387));
			fVec78[IOTA&16383] = fTemp390;
			fRec177[0] = (((fTemp288 * fVec78[(IOTA-iTemp291)&16383]) / fTemp287) + (fVec78[(IOTA-iTemp292)&16383] + (fTemp289 * fRec177[1])));
			fRec163[0] = fRec177[0];
			float fTemp391 = (fTemp39 * fRec160[1]);
			float fTemp392 = (fTemp156 * fRec182[1]);
			float fTemp393 = (fTemp156 * fRec185[1]);
			float fTemp394 = (fTemp156 * fRec188[1]);
			float fTemp395 = ((fTemp39 * fRec194[1]) + fTemp38);
			float fTemp396 = ((fTemp39 * fRec197[1]) + (fTemp37 * fTemp395));
			float fTemp397 = ((fTemp39 * fRec200[1]) + (fTemp37 * fTemp396));
			float fTemp398 = ((fTemp39 * fRec203[1]) + (fTemp37 * fTemp397));
			float fTemp399 = ((fTemp39 * fRec193[1]) + fTemp62);
			float fTemp400 = ((fTemp39 * fRec196[1]) + (fTemp37 * fTemp399));
			float fTemp401 = ((fTemp39 * fRec199[1]) + (fTemp37 * fTemp400));
			float fTemp402 = ((fTemp39 * fRec202[1]) + (fTemp37 * fTemp401));
			float fTemp403 = ((6.123234e-17f * fTemp402) - fTemp398);
			fVec79[IOTA&16383] = fTemp403;
			fRec204[0] = (((fTemp59 * fVec79[(IOTA-iTemp68)&16383]) / fTemp58) + ((fRec204[1] * fTemp60) + fVec79[(IOTA-iTemp69)&16383]));
			fRec202[0] = fRec204[0];
			float fTemp404 = (fTemp402 + (6.123234e-17f * fTemp398));
			fVec80[IOTA&16383] = fTemp404;
			fRec205[0] = (((fTemp74 * fVec80[(IOTA-iTemp77)&16383]) / fTemp73) + ((fRec205[1] * fTemp75) + fVec80[(IOTA-iTemp78)&16383]));
			fRec203[0] = fRec205[0];
			float fTemp405 = ((fTemp37 * fRec203[1]) + (fTemp20 * fTemp397));
			float fTemp406 = ((fTemp37 * fRec202[1]) + (fTemp20 * fTemp401));
			float fTemp407 = ((6.123234e-17f * fTemp406) - fTemp405);
			fVec81[IOTA&16383] = fTemp407;
			fRec201[0] = (((fTemp52 * fVec81[(IOTA-iTemp82)&16383]) / fTemp51) + ((fRec201[1] * fTemp53) + fVec81[(IOTA-iTemp83)&16383]));
			fRec199[0] = fRec201[0];
			float fTemp408 = (fTemp406 + (6.123234e-17f * fTemp405));
			fVec82[IOTA&16383] = fTemp408;
			fRec206[0] = (((fTemp88 * fVec82[(IOTA-iTemp91)&16383]) / fTemp87) + ((fRec206[1] * fTemp89) + fVec82[(IOTA-iTemp92)&16383]));
			fRec200[0] = fRec206[0];
			float fTemp409 = ((fTemp37 * fRec200[1]) + (fTemp20 * fTemp396));
			float fTemp410 = ((fTemp37 * fRec199[1]) + (fTemp20 * fTemp400));
			float fTemp411 = ((6.123234e-17f * fTemp410) - fTemp409);
			fVec83[IOTA&16383] = fTemp411;
			fRec198[0] = (((fTemp45 * fVec83[(IOTA-iTemp96)&16383]) / fTemp44) + ((fRec198[1] * fTemp46) + fVec83[(IOTA-iTemp97)&16383]));
			fRec196[0] = fRec198[0];
			float fTemp412 = (fTemp410 + (6.123234e-17f * fTemp409));
			fVec84[IOTA&16383] = fTemp412;
			fRec207[0] = (((fTemp102 * fVec84[(IOTA-iTemp105)&16383]) / fTemp101) + ((fRec207[1] * fTemp103) + fVec84[(IOTA-iTemp106)&16383]));
			fRec197[0] = fRec207[0];
			float fTemp413 = ((fTemp37 * fRec197[1]) + (fTemp20 * fTemp395));
			float fTemp414 = ((fTemp37 * fRec196[1]) + (fTemp20 * fTemp399));
			float fTemp415 = ((6.123234e-17f * fTemp414) - fTemp413);
			fVec85[IOTA&16383] = fTemp415;
			fRec195[0] = (((fTemp26 * fVec85[(IOTA-iTemp110)&16383]) / fTemp25) + ((fRec195[1] * fTemp27) + fVec85[(IOTA-iTemp111)&16383]));
			fRec193[0] = fRec195[0];
			float fTemp416 = (fTemp414 + (6.123234e-17f * fTemp413));
			fVec86[IOTA&16383] = fTemp416;
			fRec208[0] = (((fTemp116 * fVec86[(IOTA-iTemp119)&16383]) / fTemp115) + ((fRec208[1] * fTemp117) + fVec86[(IOTA-iTemp120)&16383]));
			fRec194[0] = fRec208[0];
			float fTemp417 = ((fTemp156 * fRec191[1]) + (fTemp154 * (fTemp394 + (fTemp154 * (fTemp393 + (fTemp154 * (fTemp392 + (fTemp154 * ((fTemp37 * fRec194[1]) + fTemp130)))))))));
			float fTemp418 = (fTemp156 * fRec181[1]);
			float fTemp419 = (fTemp156 * fRec184[1]);
			float fTemp420 = (fTemp156 * fRec187[1]);
			float fTemp421 = ((fTemp156 * fRec190[1]) + (fTemp154 * (fTemp420 + (fTemp154 * (fTemp419 + (fTemp154 * (fTemp418 + (fTemp154 * ((fTemp37 * fRec193[1]) + fTemp21)))))))));
			float fTemp422 = ((6.123234e-17f * fTemp421) - fTemp417);
			fVec87[IOTA&16383] = fTemp422;
			fRec192[0] = (((fTemp201 * fVec87[(IOTA-iTemp235)&16383]) / fTemp200) + ((fRec192[1] * fTemp202) + fVec87[(IOTA-iTemp236)&16383]));
			fRec190[0] = fRec192[0];
			float fTemp423 = (fTemp421 + (6.123234e-17f * fTemp417));
			fVec88[IOTA&16383] = fTemp423;
			fRec209[0] = (((fTemp241 * fVec88[(IOTA-iTemp244)&16383]) / fTemp240) + ((fRec209[1] * fTemp242) + fVec88[(IOTA-iTemp245)&16383]));
			fRec191[0] = fRec209[0];
			float fTemp424 = ((fTemp154 * fRec191[1]) + (fTemp123 * (fTemp394 + (fTemp154 * (fTemp393 + (fTemp154 * (fTemp392 + fTemp155)))))));
			float fTemp425 = ((fTemp154 * fRec190[1]) + (fTemp123 * (fTemp420 + (fTemp154 * (fTemp419 + (fTemp154 * (fTemp418 + fTemp279)))))));
			float fTemp426 = ((6.123234e-17f * fTemp425) - fTemp424);
			fVec89[IOTA&16383] = fTemp426;
			fRec189[0] = (((fTemp194 * fVec89[(IOTA-iTemp252)&16383]) / fTemp193) + ((fRec189[1] * fTemp195) + fVec89[(IOTA-iTemp253)&16383]));
			fRec187[0] = fRec189[0];
			float fTemp427 = (fTemp425 + (6.123234e-17f * fTemp424));
			fVec90[IOTA&16383] = fTemp427;
			fRec210[0] = (((fTemp258 * fVec90[(IOTA-iTemp261)&16383]) / fTemp257) + ((fRec210[1] * fTemp259) + fVec90[(IOTA-iTemp262)&16383]));
			fRec188[0] = fRec210[0];
			float fTemp428 = ((fTemp154 * fRec188[1]) + (fTemp123 * (fTemp393 + (fTemp154 * (fTemp392 + fTemp347)))));
			float fTemp429 = ((fTemp154 * fRec187[1]) + (fTemp123 * (fTemp419 + (fTemp154 * (fTemp418 + fTemp350)))));
			float fTemp430 = ((6.123234e-17f * fTemp429) - fTemp428);
			fVec91[IOTA&16383] = fTemp430;
			fRec186[0] = (((fTemp162 * fVec91[(IOTA-iTemp266)&16383]) / fTemp161) + ((fRec186[1] * fTemp163) + fVec91[(IOTA-iTemp267)&16383]));
			fRec184[0] = fRec186[0];
			float fTemp431 = (fTemp429 + (6.123234e-17f * fTemp428));
			fVec92[IOTA&16383] = fTemp431;
			fRec211[0] = (((fTemp272 * fVec92[(IOTA-iTemp275)&16383]) / fTemp271) + ((fRec211[1] * fTemp273) + fVec92[(IOTA-iTemp276)&16383]));
			fRec185[0] = fRec211[0];
			float fTemp432 = ((fTemp154 * fRec185[1]) + (fTemp123 * (fTemp392 + fTemp319)));
			float fTemp433 = ((fTemp154 * fRec184[1]) + (fTemp123 * (fTemp418 + fTemp322)));
			float fTemp434 = ((6.123234e-17f * fTemp433) - fTemp432);
			fVec93[IOTA&16383] = fTemp434;
			fRec183[0] = (((fTemp128 * fVec93[(IOTA-iTemp282)&16383]) / fTemp127) + ((fRec183[1] * fTemp129) + fVec93[(IOTA-iTemp283)&16383]));
			fRec181[0] = fRec183[0];
			float fTemp435 = (fTemp433 + (6.123234e-17f * fTemp432));
			fVec94[IOTA&16383] = fTemp435;
			fRec212[0] = (((fTemp288 * fVec94[(IOTA-iTemp291)&16383]) / fTemp287) + ((fRec212[1] * fTemp289) + fVec94[(IOTA-iTemp292)&16383]));
			fRec182[0] = fRec212[0];
			float fTemp436 = ((fTemp39 * fRec179[1]) + (fTemp37 * (fTemp391 + (fTemp37 * (fTemp368 + (fTemp37 * (fTemp341 + (fTemp37 * ((fTemp154 * fRec182[1]) + (fTemp123 * fTemp225))))))))));
			float fTemp437 = (fTemp39 * fRec105[1]);
			float fTemp438 = (fTemp39 * fRec140[1]);
			float fTemp439 = (fTemp39 * fRec159[1]);
			float fTemp440 = ((fTemp39 * fRec178[1]) + (fTemp37 * (fTemp439 + (fTemp37 * (fTemp438 + (fTemp37 * (fTemp437 + (fTemp37 * ((fTemp154 * fRec181[1]) + (fTemp123 * fTemp229))))))))));
			float fTemp441 = ((6.123234e-17f * fTemp440) - fTemp436);
			fVec95[IOTA&16383] = fTemp441;
			int iTemp442 = itbl0[iSlow30];
			fRec213[0] = ((0.0001f * iTemp442) + (0.9999f * ((iTemp3 * iTemp442) + fRec213[1])));
			float fTemp443 = (fRec213[0] + -1.49999f);
			int iTemp444 = int((int(fTemp443) & 8191));
			float fTemp445 = floorf(fTemp443);
			float fTemp446 = (fRec213[0] - fTemp445);
			float fTemp447 = (fTemp445 + (2.0f - fRec213[0]));
			fRec180[0] = (((fTemp447 * fVec95[(IOTA-iTemp444)&16383]) / fTemp446) + ((fRec180[1] * (0 - (fTemp447 / fTemp446))) + fVec95[(IOTA-int((iTemp444 + 1)))&16383]));
			fRec178[0] = fRec180[0];
			float fTemp448 = (fTemp440 + (6.123234e-17f * fTemp436));
			fVec96[IOTA&16383] = fTemp448;
			int iTemp449 = itbl0[iSlow31];
			fRec215[0] = ((0.0001f * iTemp449) + (0.9999f * ((iTemp3 * iTemp449) + fRec215[1])));
			float fTemp450 = (fRec215[0] + -1.49999f);
			int iTemp451 = int((int(fTemp450) & 8191));
			float fTemp452 = floorf(fTemp450);
			float fTemp453 = (fRec215[0] - fTemp452);
			float fTemp454 = (fTemp452 + (2.0f - fRec215[0]));
			fRec214[0] = (((fTemp454 * fVec96[(IOTA-iTemp451)&16383]) / fTemp453) + ((fRec214[1] * (0 - (fTemp454 / fTemp453))) + fVec96[(IOTA-int((iTemp451 + 1)))&16383]));
			fRec179[0] = fRec214[0];
			float fTemp455 = ((fTemp37 * fRec179[1]) + (fTemp20 * (fTemp391 + (fTemp37 * (fTemp368 + (fTemp37 * (fTemp341 + (fTemp37 * ((fTemp154 * fRec163[1]) + fTemp342)))))))));
			float fTemp456 = (fTemp123 * fTemp247);
			float fTemp457 = ((fTemp37 * fRec178[1]) + (fTemp20 * (fTemp439 + (fTemp37 * (fTemp438 + (fTemp37 * (fTemp437 + (fTemp37 * ((fTemp154 * fRec162[1]) + fTemp456)))))))));
			float fTemp458 = ((6.123234e-17f * fTemp457) - fTemp455);
			fVec97[IOTA&16383] = fTemp458;
			int iTemp459 = itbl0[iSlow33];
			fRec216[0] = ((0.001f * iTemp459) + (0.999f * ((iTemp3 * iTemp459) + fRec216[1])));
			float fTemp460 = (fRec216[0] + -1.49999f);
			int iTemp461 = int((int(fTemp460) & 8191));
			float fTemp462 = floorf(fTemp460);
			float fTemp463 = (fRec216[0] - fTemp462);
			float fTemp464 = (fTemp462 + (2.0f - fRec216[0]));
			fRec161[0] = (((fTemp464 * fVec97[(IOTA-iTemp461)&16383]) / fTemp463) + ((fRec161[1] * (0 - (fTemp464 / fTemp463))) + fVec97[(IOTA-int((iTemp461 + 1)))&16383]));
			fRec159[0] = fRec161[0];
			float fTemp465 = (fTemp457 + (6.123234e-17f * fTemp455));
			fVec98[IOTA&16383] = fTemp465;
			int iTemp466 = itbl0[iSlow34];
			fRec218[0] = ((0.001f * iTemp466) + (0.999f * ((iTemp3 * iTemp466) + fRec218[1])));
			float fTemp467 = (fRec218[0] + -1.49999f);
			int iTemp468 = int((int(fTemp467) & 8191));
			float fTemp469 = floorf(fTemp467);
			float fTemp470 = (fRec218[0] - fTemp469);
			float fTemp471 = (fTemp469 + (2.0f - fRec218[0]));
			fRec217[0] = (((fTemp471 * fVec98[(IOTA-iTemp468)&16383]) / fTemp470) + ((fRec217[1] * (0 - (fTemp471 / fTemp470))) + fVec98[(IOTA-int((iTemp468 + 1)))&16383]));
			fRec160[0] = fRec217[0];
			float fTemp472 = ((fTemp37 * fRec160[1]) + (fTemp20 * (fTemp368 + (fTemp37 * (fTemp341 + (fTemp37 * ((fTemp154 * fRec144[1]) + fTemp342)))))));
			float fTemp473 = ((fTemp37 * fRec159[1]) + (fTemp20 * (fTemp438 + (fTemp37 * (fTemp437 + (fTemp37 * ((fTemp154 * fRec143[1]) + fTemp456)))))));
			float fTemp474 = ((6.123234e-17f * fTemp473) - fTemp472);
			fVec99[IOTA&16383] = fTemp474;
			int iTemp475 = itbl0[iSlow36];
			fRec219[0] = ((0.001f * iTemp475) + (0.999f * ((iTemp3 * iTemp475) + fRec219[1])));
			float fTemp476 = (fRec219[0] + -1.49999f);
			int iTemp477 = int((int(fTemp476) & 8191));
			float fTemp478 = floorf(fTemp476);
			float fTemp479 = (fRec219[0] - fTemp478);
			float fTemp480 = (fTemp478 + (2.0f - fRec219[0]));
			fRec142[0] = (((fTemp480 * fVec99[(IOTA-iTemp477)&16383]) / fTemp479) + ((fRec142[1] * (0 - (fTemp480 / fTemp479))) + fVec99[(IOTA-int((iTemp477 + 1)))&16383]));
			fRec140[0] = fRec142[0];
			float fTemp481 = (fTemp473 + (6.123234e-17f * fTemp472));
			fVec100[IOTA&16383] = fTemp481;
			int iTemp482 = itbl0[iSlow37];
			fRec221[0] = ((0.001f * iTemp482) + (0.999f * ((iTemp3 * iTemp482) + fRec221[1])));
			float fTemp483 = (fRec221[0] + -1.49999f);
			int iTemp484 = int((int(fTemp483) & 8191));
			float fTemp485 = floorf(fTemp483);
			float fTemp486 = (fRec221[0] - fTemp485);
			float fTemp487 = (fTemp485 + (2.0f - fRec221[0]));
			fRec220[0] = (((fTemp487 * fVec100[(IOTA-iTemp484)&16383]) / fTemp486) + ((fRec220[1] * (0 - (fTemp487 / fTemp486))) + fVec100[(IOTA-int((iTemp484 + 1)))&16383]));
			fRec141[0] = fRec220[0];
			float fTemp488 = ((fTemp37 * fRec141[1]) + (fTemp20 * (fTemp341 + (fTemp37 * ((fTemp154 * fRec109[1]) + (fTemp123 * fTemp153))))));
			float fTemp489 = ((fTemp37 * fRec140[1]) + (fTemp20 * (fTemp437 + (fTemp37 * ((fTemp154 * fRec108[1]) + (fTemp123 * fTemp278))))));
			float fTemp490 = ((6.123234e-17f * fTemp489) - fTemp488);
			fVec101[IOTA&16383] = fTemp490;
			int iTemp491 = itbl0[iSlow39];
			fRec222[0] = ((0.001f * iTemp491) + (0.999f * ((iTemp3 * iTemp491) + fRec222[1])));
			float fTemp492 = (fRec222[0] + -1.49999f);
			int iTemp493 = int((int(fTemp492) & 8191));
			float fTemp494 = floorf(fTemp492);
			float fTemp495 = (fRec222[0] - fTemp494);
			float fTemp496 = (fTemp494 + (2.0f - fRec222[0]));
			fRec107[0] = (((fTemp496 * fVec101[(IOTA-iTemp493)&16383]) / fTemp495) + ((fRec107[1] * (0 - (fTemp496 / fTemp495))) + fVec101[(IOTA-int((iTemp493 + 1)))&16383]));
			fRec105[0] = fRec107[0];
			float fTemp497 = (fTemp489 + (6.123234e-17f * fTemp488));
			fVec102[IOTA&16383] = fTemp497;
			int iTemp498 = itbl0[iSlow40];
			fRec224[0] = ((0.001f * iTemp498) + (0.999f * ((iTemp3 * iTemp498) + fRec224[1])));
			float fTemp499 = (fRec224[0] + -1.49999f);
			int iTemp500 = int((int(fTemp499) & 8191));
			float fTemp501 = floorf(fTemp499);
			float fTemp502 = (fRec224[0] - fTemp501);
			float fTemp503 = (fTemp501 + (2.0f - fRec224[0]));
			fRec223[0] = (((fTemp503 * fVec102[(IOTA-iTemp500)&16383]) / fTemp502) + ((fRec223[1] * (0 - (fTemp503 / fTemp502))) + fVec102[(IOTA-int((iTemp500 + 1)))&16383]));
			fRec106[0] = fRec223[0];
			fVec103[0] = fSlow41;
			float fTemp504 = (fSlow41 + fVec103[1]);
			float fTemp505 = (1.0f - (0.5f * fTemp504));
			fRec2[0] = ((0.5f * (fTemp504 * fRec2[1])) + (fTemp505 * ((fTemp37 * fRec105[1]) + (fTemp20 * ((fTemp154 * fRec33[1]) + (fTemp123 * fTemp121))))));
			fRec0[IOTA&1023] = fRec2[0];
			fRec225[0] = ((0.5f * (fTemp504 * fRec225[1])) + (fTemp505 * ((fTemp37 * fRec106[1]) + (fTemp20 * ((fTemp154 * fRec34[1]) + (fTemp123 * fTemp346))))));
			fRec1[IOTA&1023] = fRec225[0];
			output0[i] = (FAUSTFLOAT)fRec0[(IOTA-0)&1023];
			output1[i] = (FAUSTFLOAT)fRec1[(IOTA-0)&1023];
			// post processing
			fRec225[1] = fRec225[0];
			fRec2[1] = fRec2[0];
			fVec103[1] = fVec103[0];
			fRec106[1] = fRec106[0];
			fRec223[1] = fRec223[0];
			fRec224[1] = fRec224[0];
			fRec105[1] = fRec105[0];
			fRec107[1] = fRec107[0];
			fRec222[1] = fRec222[0];
			fRec141[1] = fRec141[0];
			fRec220[1] = fRec220[0];
			fRec221[1] = fRec221[0];
			fRec140[1] = fRec140[0];
			fRec142[1] = fRec142[0];
			fRec219[1] = fRec219[0];
			fRec160[1] = fRec160[0];
			fRec217[1] = fRec217[0];
			fRec218[1] = fRec218[0];
			fRec159[1] = fRec159[0];
			fRec161[1] = fRec161[0];
			fRec216[1] = fRec216[0];
			fRec179[1] = fRec179[0];
			fRec214[1] = fRec214[0];
			fRec215[1] = fRec215[0];
			fRec178[1] = fRec178[0];
			fRec180[1] = fRec180[0];
			fRec213[1] = fRec213[0];
			fRec182[1] = fRec182[0];
			fRec212[1] = fRec212[0];
			fRec181[1] = fRec181[0];
			fRec183[1] = fRec183[0];
			fRec185[1] = fRec185[0];
			fRec211[1] = fRec211[0];
			fRec184[1] = fRec184[0];
			fRec186[1] = fRec186[0];
			fRec188[1] = fRec188[0];
			fRec210[1] = fRec210[0];
			fRec187[1] = fRec187[0];
			fRec189[1] = fRec189[0];
			fRec191[1] = fRec191[0];
			fRec209[1] = fRec209[0];
			fRec190[1] = fRec190[0];
			fRec192[1] = fRec192[0];
			fRec194[1] = fRec194[0];
			fRec208[1] = fRec208[0];
			fRec193[1] = fRec193[0];
			fRec195[1] = fRec195[0];
			fRec197[1] = fRec197[0];
			fRec207[1] = fRec207[0];
			fRec196[1] = fRec196[0];
			fRec198[1] = fRec198[0];
			fRec200[1] = fRec200[0];
			fRec206[1] = fRec206[0];
			fRec199[1] = fRec199[0];
			fRec201[1] = fRec201[0];
			fRec203[1] = fRec203[0];
			fRec205[1] = fRec205[0];
			fRec202[1] = fRec202[0];
			fRec204[1] = fRec204[0];
			fRec163[1] = fRec163[0];
			fRec177[1] = fRec177[0];
			fRec162[1] = fRec162[0];
			fRec164[1] = fRec164[0];
			fRec166[1] = fRec166[0];
			fRec176[1] = fRec176[0];
			fRec165[1] = fRec165[0];
			fRec167[1] = fRec167[0];
			fRec169[1] = fRec169[0];
			fRec175[1] = fRec175[0];
			fRec168[1] = fRec168[0];
			fRec170[1] = fRec170[0];
			fRec172[1] = fRec172[0];
			fRec174[1] = fRec174[0];
			fRec171[1] = fRec171[0];
			fRec173[1] = fRec173[0];
			fRec144[1] = fRec144[0];
			fRec158[1] = fRec158[0];
			fRec143[1] = fRec143[0];
			fRec145[1] = fRec145[0];
			fRec147[1] = fRec147[0];
			fRec157[1] = fRec157[0];
			fRec146[1] = fRec146[0];
			fRec148[1] = fRec148[0];
			fRec150[1] = fRec150[0];
			fRec156[1] = fRec156[0];
			fRec149[1] = fRec149[0];
			fRec151[1] = fRec151[0];
			fRec153[1] = fRec153[0];
			fRec155[1] = fRec155[0];
			fRec152[1] = fRec152[0];
			fRec154[1] = fRec154[0];
			fRec109[1] = fRec109[0];
			fRec139[1] = fRec139[0];
			fRec108[1] = fRec108[0];
			fRec110[1] = fRec110[0];
			fRec112[1] = fRec112[0];
			fRec138[1] = fRec138[0];
			fRec111[1] = fRec111[0];
			fRec113[1] = fRec113[0];
			fRec115[1] = fRec115[0];
			fRec137[1] = fRec137[0];
			fRec114[1] = fRec114[0];
			fRec116[1] = fRec116[0];
			fRec118[1] = fRec118[0];
			fRec136[1] = fRec136[0];
			fRec117[1] = fRec117[0];
			fRec119[1] = fRec119[0];
			fRec121[1] = fRec121[0];
			fRec135[1] = fRec135[0];
			fRec120[1] = fRec120[0];
			fRec122[1] = fRec122[0];
			fRec124[1] = fRec124[0];
			fRec134[1] = fRec134[0];
			fRec123[1] = fRec123[0];
			fRec125[1] = fRec125[0];
			fRec127[1] = fRec127[0];
			fRec133[1] = fRec133[0];
			fRec126[1] = fRec126[0];
			fRec128[1] = fRec128[0];
			fRec130[1] = fRec130[0];
			fRec132[1] = fRec132[0];
			fRec129[1] = fRec129[0];
			fRec131[1] = fRec131[0];
			fRec34[1] = fRec34[0];
			fRec103[1] = fRec103[0];
			fRec104[1] = fRec104[0];
			fRec33[1] = fRec33[0];
			fRec35[1] = fRec35[0];
			fRec54[1] = fRec54[0];
			fRec101[1] = fRec101[0];
			fRec102[1] = fRec102[0];
			fRec53[1] = fRec53[0];
			fRec55[1] = fRec55[0];
			fRec74[1] = fRec74[0];
			fRec99[1] = fRec99[0];
			fRec100[1] = fRec100[0];
			fRec73[1] = fRec73[0];
			fRec75[1] = fRec75[0];
			fRec78[1] = fRec78[0];
			fRec97[1] = fRec97[0];
			fRec98[1] = fRec98[0];
			fRec77[1] = fRec77[0];
			fRec79[1] = fRec79[0];
			fRec82[1] = fRec82[0];
			fRec96[1] = fRec96[0];
			fRec81[1] = fRec81[0];
			fRec83[1] = fRec83[0];
			fRec85[1] = fRec85[0];
			fRec95[1] = fRec95[0];
			fRec84[1] = fRec84[0];
			fRec86[1] = fRec86[0];
			fRec88[1] = fRec88[0];
			fRec94[1] = fRec94[0];
			fRec87[1] = fRec87[0];
			fRec89[1] = fRec89[0];
			fRec91[1] = fRec91[0];
			fRec93[1] = fRec93[0];
			fRec90[1] = fRec90[0];
			fRec92[1] = fRec92[0];
			fRec80[1] = fRec80[0];
			fRec76[1] = fRec76[0];
			fRec58[1] = fRec58[0];
			fRec72[1] = fRec72[0];
			fRec57[1] = fRec57[0];
			fRec59[1] = fRec59[0];
			fRec61[1] = fRec61[0];
			fRec71[1] = fRec71[0];
			fRec60[1] = fRec60[0];
			fRec62[1] = fRec62[0];
			fRec64[1] = fRec64[0];
			fRec70[1] = fRec70[0];
			fRec63[1] = fRec63[0];
			fRec65[1] = fRec65[0];
			fRec67[1] = fRec67[0];
			fRec69[1] = fRec69[0];
			fRec66[1] = fRec66[0];
			fRec68[1] = fRec68[0];
			fRec56[1] = fRec56[0];
			fRec38[1] = fRec38[0];
			fRec52[1] = fRec52[0];
			fRec37[1] = fRec37[0];
			fRec39[1] = fRec39[0];
			fRec41[1] = fRec41[0];
			fRec51[1] = fRec51[0];
			fRec40[1] = fRec40[0];
			fRec42[1] = fRec42[0];
			fRec44[1] = fRec44[0];
			fRec50[1] = fRec50[0];
			fRec43[1] = fRec43[0];
			fRec45[1] = fRec45[0];
			fRec47[1] = fRec47[0];
			fRec49[1] = fRec49[0];
			fRec46[1] = fRec46[0];
			fRec48[1] = fRec48[0];
			fRec36[1] = fRec36[0];
			fRec10[1] = fRec10[0];
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fRec9[1] = fRec9[0];
			fRec11[1] = fRec11[0];
			fRec14[1] = fRec14[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			fRec18[1] = fRec18[0];
			fRec27[1] = fRec27[0];
			fRec28[1] = fRec28[0];
			fRec17[1] = fRec17[0];
			fRec19[1] = fRec19[0];
			fRec22[1] = fRec22[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec20[1] = fRec20[0];
			fRec16[1] = fRec16[0];
			fRec12[1] = fRec12[0];
			fVec5[1] = fVec5[0];
			fVec4[1] = fVec4[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			IOTA = IOTA+1;
			fVec2[1] = fVec2[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fVec1[1] = fVec1[0];
			iVec0[1] = iVec0[0];
		}
	}
};


int 	mydsp::SIG0::iWave0[1302] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,1163,1171,1181,1187,1193,1201,1213,1217,1223,1229,1231,1237,1249,1259,1277,1279,1283,1289,1291,1297,1301,1303,1307,1319,1321,1327,1361,1367,1373,1381,1399,1409,1423,1427,1429,1433,1439,1447,1451,1453,1459,1471,1481,1483,1487,1489,1493,1499,1511,1523,1531,1543,1549,1553,1559,1567,1571,1579,1583,1597,1601,1607,1609,1613,1619,1621,1627,1637,1657,1663,1667,1669,1693,1697,1699,1709,1721,1723,1733,1741,1747,1753,1759,1777,1783,1787,1789,1801,1811,1823,1831,1847,1861,1867,1871,1873,1877,1879,1889,1901,1907,1913,1931,1933,1949,1951,1973,1979,1987,1993,1997,1999,2003,2011,2017,2027,2029,2039,2053,2063,2069,2081,2083,2087,2089,2099,2111,2113,2129,2131,2137,2141,2143,2153,2161,2179,2203,2207,2213,2221,2237,2239,2243,2251,2267,2269,2273,2281,2287,2293,2297,2309,2311,2333,2339,2341,2347,2351,2357,2371,2377,2381,2383,2389,2393,2399,2411,2417,2423,2437,2441,2447,2459,2467,2473,2477,2503,2521,2531,2539,2543,2549,2551,2557,2579,2591,2593,2609,2617,2621,2633,2647,2657,2659,2663,2671,2677,2683,2687,2689,2693,2699,2707,2711,2713,2719,2729,2731,2741,2749,2753,2767,2777,2789,2791,2797,2801,2803,2819,2833,2837,2843,2851,2857,2861,2879,2887,2897,2903,2909,2917,2927,2939,2953,2957,2963,2969,2971,2999,3001,3011,3019,3023,3037,3041,3049,3061,3067,3079,3083,3089,3109,3119,3121,3137,3163,3167,3169,3181,3187,3191,3203,3209,3217,3221,3229,3251,3253,3257,3259,3271,3299,3301,3307,3313,3319,3323,3329,3331,3343,3347,3359,3361,3371,3373,3389,3391,3407,3413,3433,3449,3457,3461,3463,3467,3469,3491,3499,3511,3517,3527,3529,3533,3539,3541,3547,3557,3559,3571,3581,3583,3593,3607,3613,3617,3623,3631,3637,3643,3659,3671,3673,3677,3691,3697,3701,3709,3719,3727,3733,3739,3761,3767,3769,3779,3793,3797,3803,3821,3823,3833,3847,3851,3853,3863,3877,3881,3889,3907,3911,3917,3919,3923,3929,3931,3943,3947,3967,3989,4001,4003,4007,4013,4019,4021,4027,4049,4051,4057,4073,4079,4091,4093,4099,4111,4127,4129,4133,4139,4153,4157,4159,4177,4201,4211,4217,4219,4229,4231,4241,4243,4253,4259,4261,4271,4273,4283,4289,4297,4327,4337,4339,4349,4357,4363,4373,4391,4397,4409,4421,4423,4441,4447,4451,4457,4463,4481,4483,4493,4507,4513,4517,4519,4523,4547,4549,4561,4567,4583,4591,4597,4603,4621,4637,4639,4643,4649,4651,4657,4663,4673,4679,4691,4703,4721,4723,4729,4733,4751,4759,4783,4787,4789,4793,4799,4801,4813,4817,4831,4861,4871,4877,4889,4903,4909,4919,4931,4933,4937,4943,4951,4957,4967,4969,4973,4987,4993,4999,5003,5009,5011,5021,5023,5039,5051,5059,5077,5081,5087,5099,5101,5107,5113,5119,5147,5153,5167,5171,5179,5189,5197,5209,5227,5231,5233,5237,5261,5273,5279,5281,5297,5303,5309,5323,5333,5347,5351,5381,5387,5393,5399,5407,5413,5417,5419,5431,5437,5441,5443,5449,5471,5477,5479,5483,5501,5503,5507,5519,5521,5527,5531,5557,5563,5569,5573,5581,5591,5623,5639,5641,5647,5651,5653,5657,5659,5669,5683,5689,5693,5701,5711,5717,5737,5741,5743,5749,5779,5783,5791,5801,5807,5813,5821,5827,5839,5843,5849,5851,5857,5861,5867,5869,5879,5881,5897,5903,5923,5927,5939,5953,5981,5987,6007,6011,6029,6037,6043,6047,6053,6067,6073,6079,6089,6091,6101,6113,6121,6131,6133,6143,6151,6163,6173,6197,6199,6203,6211,6217,6221,6229,6247,6257,6263,6269,6271,6277,6287,6299,6301,6311,6317,6323,6329,6337,6343,6353,6359,6361,6367,6373,6379,6389,6397,6421,6427,6449,6451,6469,6473,6481,6491,6521,6529,6547,6551,6553,6563,6569,6571,6577,6581,6599,6607,6619,6637,6653,6659,6661,6673,6679,6689,6691,6701,6703,6709,6719,6733,6737,6761,6763,6779,6781,6791,6793,6803,6823,6827,6829,6833,6841,6857,6863,6869,6871,6883,6899,6907,6911,6917,6947,6949,6959,6961,6967,6971,6977,6983,6991,6997,7001,7013,7019,7027,7039,7043,7057,7069,7079,7103,7109,7121,7127,7129,7151,7159,7177,7187,7193,7207,7211,7213,7219,7229,7237,7243,7247,7253,7283,7297,7307,7309,7321,7331,7333,7349,7351,7369,7393,7411,7417,7433,7451,7457,7459,7477,7481,7487,7489,7499,7507,7517,7523,7529,7537,7541,7547,7549,7559,7561,7573,7577,7583,7589,7591,7603,7607,7621,7639,7643,7649,7669,7673,7681,7687,7691,7699,7703,7717,7723,7727,7741,7753,7757,7759,7789,7793,7817,7823,7829,7841,7853,7867,7873,7877,7879,7883,7901,7907,7919,7927,7933,7937,7949,7951,7963,7993,8009,8011,8017,8039,8053,8059,8069,8081,8087,8089,8093,8101,8111,8117,8123,8147,8161,8167,8171,8179,8191,8209,8219,8221,8231,8233,8237,8243,8263,8269,8273,8287,8291,8293,8297,8311,8317,8329,8353,8363,8369,8377,8387,8389,8419,8423,8429,8431,8443,8447,8461,8467,8501,8513,8521,8527,8537,8539,8543,8563,8573,8581,8597,8599,8609,8623,8627,8629,8641,8647,8663,8669,8677,8681,8689,8693,8699,8707,8713,8719,8731,8737,8741,8747,8753,8761,8779,8783,8803,8807,8819,8821,8831,8837,8839,8849,8861,8863,8867,8887,8893,8923,8929,8933,8941,8951,8963,8969,8971,8999,9001,9007,9011,9013,9029,9041,9043,9049,9059,9067,9091,9103,9109,9127,9133,9137,9151,9157,9161,9173,9181,9187,9199,9203,9209,9221,9227,9239,9241,9257,9277,9281,9283,9293,9311,9319,9323,9337,9341,9343,9349,9371,9377,9391,9397,9403,9413,9419,9421,9431,9433,9437,9439,9461,9463,9467,9473,9479,9491,9497,9511,9521,9533,9539,9547,9551,9587,9601,9613,9619,9623,9629,9631,9643,9649,9661,9677,9679,9689,9697,9719,9721,9733,9739,9743,9749,9767,9769,9781,9787,9791,9803,9811,9817,9829,9833,9839,9851,9857,9859,9871,9883,9887,9901,9907,9923,9929,9931,9941,9949,9967,9973,10007,10009,10037,10039,10061,10067,10069,10079,10091,10093,10099,10103,10111,10133,10139,10141,10151,10159,10163,10169,10177,10181,10193,10211,10223,10243,10247,10253,10259,10267,10271,10273,10289,10301,10303,10313,10321,10331,10333,10337,10343,10357,10369,10391,10399,10427,10429,10433,10453,10457,10459,10463,10477,10487,10499,10501,10513,10529,10531,10559,10567,10589,10597,10601,10607,10613,10627,10631,10639,10651,10657,10663,10667};
int 	mydsp::itbl0[1302];

#include <stdio.h>
#include <string>
#include "m_pd.h"

#define sym(name) xsym(name)
#define xsym(name) #name
#define faust_setup(name) xfaust_setup(name)
#define xfaust_setup(name) name ## _tilde_setup(void)

// time for "active" toggle xfades in secs
#define XFADE_TIME 0.1f

static t_class *faust_class;

struct t_faust {
  t_object x_obj;
#ifdef __MINGW32__
  /* This seems to be necessary as some as yet undetermined Pd routine seems
     to write past the end of x_obj on Windows. */
  int fence; /* dummy field (not used) */
#endif
  mydsp *dsp;
  PdUI *ui;
  std::string *label;
  int active, xfade, n_xfade, rate, n_in, n_out;
  t_sample **inputs, **outputs, **buf;
  t_outlet *out;
  t_sample f;
};

static t_symbol *s_button, *s_checkbox, *s_vslider, *s_hslider, *s_nentry,
  *s_vbargraph, *s_hbargraph;

static inline void zero_samples(int k, int n, t_sample **out)
{
  for (int i = 0; i < k; i++)
#ifdef __STDC_IEC_559__
    /* IEC 559 a.k.a. IEEE 754 floats can be initialized faster like this */
    memset(out[i], 0, n*sizeof(t_sample));
#else
    for (int j = 0; j < n; j++)
      out[i][j] = 0.0f;
#endif
}

static inline void copy_samples(int k, int n, t_sample **out, t_sample **in)
{
  for (int i = 0; i < k; i++)
    memcpy(out[i], in[i], n*sizeof(t_sample));
}

static t_int *faust_perform(t_int *w)
{
  t_faust *x = (t_faust *)(w[1]);
  int n = (int)(w[2]);
  if (!x->dsp || !x->buf) return (w+3);
  AVOIDDENORMALS;
  if (x->xfade > 0) {
    float d = 1.0f/x->n_xfade, f = (x->xfade--)*d;
    d = d/n;
    x->dsp->compute(n, x->inputs, x->buf);
    if (x->active)
      if (x->n_in == x->n_out)
	/* xfade inputs -> buf */
	for (int j = 0; j < n; j++, f -= d)
	  for (int i = 0; i < x->n_out; i++)
	    x->outputs[i][j] = f*x->inputs[i][j]+(1.0f-f)*x->buf[i][j];
      else
	/* xfade 0 -> buf */
	for (int j = 0; j < n; j++, f -= d)
	  for (int i = 0; i < x->n_out; i++)
	    x->outputs[i][j] = (1.0f-f)*x->buf[i][j];
    else
      if (x->n_in == x->n_out)
	/* xfade buf -> inputs */
	for (int j = 0; j < n; j++, f -= d)
	  for (int i = 0; i < x->n_out; i++)
	    x->outputs[i][j] = f*x->buf[i][j]+(1.0f-f)*x->inputs[i][j];
      else
	/* xfade buf -> 0 */
	for (int j = 0; j < n; j++, f -= d)
	  for (int i = 0; i < x->n_out; i++)
	    x->outputs[i][j] = f*x->buf[i][j];
  } else if (x->active) {
    x->dsp->compute(n, x->inputs, x->buf);
    copy_samples(x->n_out, n, x->outputs, x->buf);
  } else if (x->n_in == x->n_out) {
    copy_samples(x->n_out, n, x->buf, x->inputs);
    copy_samples(x->n_out, n, x->outputs, x->buf);
  } else
    zero_samples(x->n_out, n, x->outputs);
  return (w+3);
}

static void faust_dsp(t_faust *x, t_signal **sp)
{
  int n = sp[0]->s_n, sr = (int)sp[0]->s_sr;
  if (x->rate <= 0) {
    /* default sample rate is whatever Pd tells us */
    PdUI *ui = x->ui;
    float *z = NULL;
    if (ui->nelems > 0 &&
	(z = (float*)malloc(ui->nelems*sizeof(float)))) {
      /* save the current control values */
      for (int i = 0; i < ui->nelems; i++)
	if (ui->elems[i].zone)
	  z[i] = *ui->elems[i].zone;
    }
    /* set the proper sample rate; this requires reinitializing the dsp */
    x->rate = sr;
    x->dsp->init(sr);
    if (z) {
      /* restore previous control values */
      for (int i = 0; i < ui->nelems; i++)
	if (ui->elems[i].zone)
	  *ui->elems[i].zone = z[i];
      free(z);
    }
  }
  if (n > 0)
    x->n_xfade = (int)(x->rate*XFADE_TIME/n);
  dsp_add(faust_perform, 2, x, n);
  for (int i = 0; i < x->n_in; i++)
    x->inputs[i] = sp[i+1]->s_vec;
  for (int i = 0; i < x->n_out; i++)
    x->outputs[i] = sp[x->n_in+i+1]->s_vec;
  if (x->buf != NULL)
    for (int i = 0; i < x->n_out; i++) {
      x->buf[i] = (t_sample*)malloc(n*sizeof(t_sample));
      if (x->buf[i] == NULL) {
	for (int j = 0; j < i; j++)
	  free(x->buf[j]);
	free(x->buf);
	x->buf = NULL;
	break;
      }
    }
}

static int pathcmp(const char *s, const char *t)
{
  int n = strlen(s), m = strlen(t);
  if (n == 0 || m == 0)
    return 0;
  else if (t[0] == '/')
    return strcmp(s, t);
  else if (n <= m || s[n-m-1] != '/')
    return strcmp(s+1, t);
  else
    return strcmp(s+n-m, t);
}

static void faust_any(t_faust *x, t_symbol *s, int argc, t_atom *argv)
{
  if (!x->dsp) return;
  PdUI *ui = x->ui;
  if (s == &s_bang) {
    for (int i = 0; i < ui->nelems; i++)
      if (ui->elems[i].label && ui->elems[i].zone) {
	t_atom args[6];
	t_symbol *_s;
	switch (ui->elems[i].type) {
	case UI_BUTTON:
	  _s = s_button;
	  break;
	case UI_CHECK_BUTTON:
	  _s = s_checkbox;
	  break;
	case UI_V_SLIDER:
	  _s = s_vslider;
	  break;
	case UI_H_SLIDER:
	  _s = s_hslider;
	  break;
	case UI_NUM_ENTRY:
	  _s = s_nentry;
	  break;
	case UI_V_BARGRAPH:
	  _s = s_vbargraph;
	  break;
	case UI_H_BARGRAPH:
	  _s = s_hbargraph;
	  break;
	default:
	  continue;
	}
	SETSYMBOL(&args[0], gensym(ui->elems[i].label));
	SETFLOAT(&args[1], *ui->elems[i].zone);
	SETFLOAT(&args[2], ui->elems[i].init);
	SETFLOAT(&args[3], ui->elems[i].min);
	SETFLOAT(&args[4], ui->elems[i].max);
	SETFLOAT(&args[5], ui->elems[i].step);
	outlet_anything(x->out, _s, 6, args);
      }
  } else {
    const char *label = s->s_name;
    int count = 0;
    for (int i = 0; i < ui->nelems; i++)
      if (ui->elems[i].label &&
	  pathcmp(ui->elems[i].label, label) == 0) {
	if (argc == 0) {
	  if (ui->elems[i].zone) {
	    t_atom arg;
	    SETFLOAT(&arg, *ui->elems[i].zone);
	    outlet_anything(x->out, gensym(ui->elems[i].label), 1, &arg);
	  }
	  ++count;
	} else if (argc == 1 &&
		   (argv[0].a_type == A_FLOAT ||
		    argv[0].a_type == A_DEFFLOAT) &&
		   ui->elems[i].zone) {
	  float f = atom_getfloat(argv);
	  *ui->elems[i].zone = f;
	  ++count;
	} else
	  pd_error(x, "[faust] %s: bad control argument: %s",
		   x->label->c_str(), label);
      }
    if (count == 0 && strcmp(label, "active") == 0) {
      if (argc == 0) {
	t_atom arg;
	SETFLOAT(&arg, (float)x->active);
	outlet_anything(x->out, gensym((char*)"active"), 1, &arg);
      } else if (argc == 1 &&
		 (argv[0].a_type == A_FLOAT ||
		  argv[0].a_type == A_DEFFLOAT)) {
	float f = atom_getfloat(argv);
	x->active = (int)f;
	x->xfade = x->n_xfade;
      }
    }
  }
}

static void faust_free(t_faust *x)
{
  if (x->label) delete x->label;
  if (x->dsp) delete x->dsp;
  if (x->ui) delete x->ui;
  if (x->inputs) free(x->inputs);
  if (x->outputs) free(x->outputs);
  if (x->buf) {
    for (int i = 0; i < x->n_out; i++)
      if (x->buf[i]) free(x->buf[i]);
    free(x->buf);
  }
}

static void *faust_new(t_symbol *s, int argc, t_atom *argv)
{
  t_faust *x = (t_faust*)pd_new(faust_class);
  int sr = -1;
  t_symbol *id = NULL;
  x->active = 1;
  for (int i = 0; i < argc; i++)
    if (argv[i].a_type == A_FLOAT || argv[i].a_type == A_DEFFLOAT)
      sr = (int)argv[i].a_w.w_float;
    else if (argv[i].a_type == A_SYMBOL || argv[i].a_type == A_DEFSYMBOL)
      id = argv[i].a_w.w_symbol;
  x->rate = sr;
  if (sr <= 0) sr = 44100;
  x->xfade = 0; x->n_xfade = (int)(sr*XFADE_TIME/64);
  x->inputs = x->outputs = x->buf = NULL;
    x->label = new std::string(sym(mydsp) "~");
  x->dsp = new mydsp();
  x->ui = new PdUI(sym(mydsp), id?id->s_name:NULL);
  if (!x->dsp || !x->ui || !x->label) goto error;
  if (id) {
    *x->label += " ";
    *x->label += id->s_name;
  }
  x->n_in = x->dsp->getNumInputs();
  x->n_out = x->dsp->getNumOutputs();
  if (x->n_in > 0)
    x->inputs = (t_sample**)malloc(x->n_in*sizeof(t_sample*));
  if (x->n_out > 0) {
    x->outputs = (t_sample**)malloc(x->n_out*sizeof(t_sample*));
    x->buf = (t_sample**)malloc(x->n_out*sizeof(t_sample*));
  }
  if ((x->n_in > 0 && x->inputs == NULL) ||
      (x->n_out > 0 && (x->outputs == NULL || x->buf == NULL)))
    goto error;
  for (int i = 0; i < x->n_out; i++)
    x->buf[i] = NULL;
  x->dsp->init(sr);
  x->dsp->buildUserInterface(x->ui);
  for (int i = 0; i < x->n_in; i++)
    inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  x->out = outlet_new(&x->x_obj, 0);
  for (int i = 0; i < x->n_out; i++)
    outlet_new(&x->x_obj, &s_signal);
  return (void *)x;
 error:
  faust_free(x);
  x->dsp = NULL; x->ui = NULL;
  x->inputs = x->outputs = x->buf = NULL;
  return (void *)x;
}

extern "C" void faust_setup(mydsp)
{
  t_symbol *s = gensym(sym(mydsp) "~");
  faust_class =
    class_new(s, (t_newmethod)faust_new, (t_method)faust_free,
	      sizeof(t_faust), CLASS_DEFAULT,
	      A_GIMME, A_NULL);
  class_addmethod(faust_class, (t_method)faust_dsp, gensym((char*)"dsp"), A_NULL);
  class_addanything(faust_class, faust_any);
  class_addmethod(faust_class, nullfn, &s_signal, A_NULL);
  s_button = gensym((char*)"button");
  s_checkbox = gensym((char*)"checkbox");
  s_vslider = gensym((char*)"vslider");
  s_hslider = gensym((char*)"hslider");
  s_nentry = gensym((char*)"nentry");
  s_vbargraph = gensym((char*)"vbargraph");
  s_hbargraph = gensym((char*)"hbargraph");
  /* give some indication that we're loaded and ready to go */
  mydsp dsp = mydsp();
  post("[faust] %s: %d inputs, %d outputs", sym(mydsp) "~",
       dsp.getNumInputs(), dsp.getNumOutputs());
}

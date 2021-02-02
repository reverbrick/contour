/* ------------------------------------------------------------
name: "VirtualAnalogSynth"
Code generated with Faust 2.20.0 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale &
 Aalborg University (Copenhagen, Denmark)
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

#include "VirtualAnalogSynth.h"

/************************** BEGIN meta.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __meta__
#define __meta__

struct Meta
{
    virtual ~Meta() {};
    virtual void declare(const char* key, const char* value) = 0;
    
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

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
         * Trigger the ui_interface parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceInit(int sample_rate) = 0;

        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
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
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
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
/**************************  END  dsp.h **************************/
/************************** BEGIN MapUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>

/************************** BEGIN UI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
class UIReal
{
    
    public:
        
        UIReal() {}
        virtual ~UIReal() {}
        
        // -- widget's layouts
        
        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;
        
        // -- active widgets
        
        virtual void addButton(const char* label, REAL* zone) = 0;
        virtual void addCheckButton(const char* label, REAL* zone) = 0;
        virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
        virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
        virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
        
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
        virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
        
        // -- soundfiles
        
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
        
        // -- metadata declarations
        
        virtual void declare(REAL* zone, const char* key, const char* val) {}
};

class UI : public UIReal<FAUSTFLOAT>
{

    public:

        UI() {}
        virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            std::replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
        void pushLabel(const std::string& label) { fControlsLevel.push_back(label); }
        void popLabel() { fControlsLevel.pop_back(); }
    
};

#endif  // FAUST_PATHBUILDER_H
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {};
        virtual ~MapUI() {};
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return FAUSTFLOAT(0);
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        std::string getParamAddress(int index)
        { 
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            while (index-- > 0 && it++ != fPathZoneMap.end()) {}
            return (*it).first;
        }
    
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            do {
                if ((*it).second == zone) return (*it).first;
            }
            while (it++ != fPathZoneMap.end());
            return "";
        }
    
        static bool endsWith(std::string const& str, std::string const& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
};


#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>

static float mydsp_faustpower2_f(float value) {
	return (value * value);
}
static float mydsp_faustpower3_f(float value) {
	return ((value * value) * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fHslider0;
	int iVec0[4];
	float fRec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fEntry0;
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fVslider2;
	float fRec2[2];
	float fVec1[2];
	float fRec1[2];
	float fConst2;
	float fVec2[2];
	float fConst3;
	float fVec3[2];
	float fVec4[2];
	float fConst4;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec3[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec4[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	float fConst5;
	FAUSTFLOAT fVslider5;
	float fVec22[2];
	float fRec5[2];
	float fVec23[2];
	int IOTA;
	float fVec24[4096];
	float fConst6;
	float fVec25[2];
	float fRec6[2];
	float fVec26[2];
	float fVec27[4096];
	float fVec28[2];
	float fRec7[2];
	float fVec29[2];
	float fVec30[4096];
	float fConst7;
	FAUSTFLOAT fVslider6;
	float fRec8[2];
	float fRec9[2];
	float fRec10[2];
	FAUSTFLOAT fVslider7;
	float fConst8;
	FAUSTFLOAT fCheckbox0;
	float fVec31[2];
	float fVec32[2];
	float fVec33[4096];
	FAUSTFLOAT fVslider8;
	float fRec11[2];
	float fVec34[2];
	float fVec35[2];
	float fVec36[4096];
	float fVec37[2];
	float fVec38[2];
	float fVec39[4096];
	FAUSTFLOAT fVslider9;
	int iRec13[2];
	float fRec12[4];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("filename", "VirtualAnalogSynth.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "VirtualAnalogSynth");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (1.0f / fConst0);
		fConst2 = (0.25f * fConst0);
		fConst3 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst4 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst5 = (0.0833333358f * fConst0);
		fConst6 = (0.5f * fConst0);
		fConst7 = (1.33333337f / fConst0);
		fConst8 = (0.013888889f * fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(-20.0f);
		fVslider1 = FAUSTFLOAT(1.0f);
		fEntry0 = FAUSTFLOAT(2.0f);
		fHslider1 = FAUSTFLOAT(49.0f);
		fVslider2 = FAUSTFLOAT(0.10000000000000001f);
		fVslider3 = FAUSTFLOAT(-0.10000000000000001f);
		fVslider4 = FAUSTFLOAT(0.10000000000000001f);
		fVslider5 = FAUSTFLOAT(0.0f);
		fVslider6 = FAUSTFLOAT(0.0f);
		fVslider7 = FAUSTFLOAT(0.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fVslider8 = FAUSTFLOAT(0.5f);
		fVslider9 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec1[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec2[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec3[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fVec4[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec5[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec6[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec7[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fVec8[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec3[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fVec9[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fVec10[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec11[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec12[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fVec13[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec14[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fVec15[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec4[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fVec16[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fVec17[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fVec18[l23] = 0.0f;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec19[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec20[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fVec21[l26] = 0.0f;
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fVec22[l27] = 0.0f;
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec5[l28] = 0.0f;
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fVec23[l29] = 0.0f;
		}
		IOTA = 0;
		for (int l30 = 0; (l30 < 4096); l30 = (l30 + 1)) {
			fVec24[l30] = 0.0f;
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fVec25[l31] = 0.0f;
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec6[l32] = 0.0f;
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fVec26[l33] = 0.0f;
		}
		for (int l34 = 0; (l34 < 4096); l34 = (l34 + 1)) {
			fVec27[l34] = 0.0f;
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fVec28[l35] = 0.0f;
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec7[l36] = 0.0f;
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fVec29[l37] = 0.0f;
		}
		for (int l38 = 0; (l38 < 4096); l38 = (l38 + 1)) {
			fVec30[l38] = 0.0f;
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec8[l39] = 0.0f;
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec9[l40] = 0.0f;
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec10[l41] = 0.0f;
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fVec31[l42] = 0.0f;
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fVec32[l43] = 0.0f;
		}
		for (int l44 = 0; (l44 < 4096); l44 = (l44 + 1)) {
			fVec33[l44] = 0.0f;
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec11[l45] = 0.0f;
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fVec34[l46] = 0.0f;
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fVec35[l47] = 0.0f;
		}
		for (int l48 = 0; (l48 < 4096); l48 = (l48 + 1)) {
			fVec36[l48] = 0.0f;
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fVec37[l49] = 0.0f;
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fVec38[l50] = 0.0f;
		}
		for (int l51 = 0; (l51 < 4096); l51 = (l51 + 1)) {
			fVec39[l51] = 0.0f;
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			iRec13[l52] = 0;
		}
		for (int l53 = 0; (l53 < 4); l53 = (l53 + 1)) {
			fRec12[l53] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's oscillators.lib for documentation and references");
		ui_interface->openVerticalBox("VIRTUAL ANALOG OSCILLATORS");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("Signal Levels");
		ui_interface->declare(&fVslider1, "0", "");
		ui_interface->declare(&fVslider1, "style", "vslider");
		ui_interface->addVerticalSlider("Sawtooth", &fVslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Pulse Train");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When checked, use 3rd-order aliasing suppression (up from 2)  See if you can hear a difference with the freq high and swept");
		ui_interface->addCheckButton("Order 3", &fCheckbox0);
		ui_interface->declare(&fVslider7, "1", "");
		ui_interface->declare(&fVslider7, "style", "vslider");
		ui_interface->addVerticalSlider("0x00", &fVslider7, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fVslider8, "2", "");
		ui_interface->declare(&fVslider8, "style", "knob");
		ui_interface->addVerticalSlider("Duty Cycle", &fVslider8, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(&fVslider5, "2", "");
		ui_interface->declare(&fVslider5, "style", "vslider");
		ui_interface->addVerticalSlider("Square", &fVslider5, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fVslider6, "3", "");
		ui_interface->declare(&fVslider6, "style", "vslider");
		ui_interface->addVerticalSlider("Triangle", &fVslider6, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fVslider9, "4", "");
		ui_interface->declare(&fVslider9, "style", "vslider");
		ui_interface->declare(&fVslider9, "tooltip", "Pink Noise (or 1/f noise) is   Constant-Q Noise, meaning that it has the same total power in every octave   (uses only amplitude controls)");
		ui_interface->addVerticalSlider("Pink Noise", &fVslider9, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fVslider0, "5", "");
		ui_interface->declare(&fVslider0, "style", "vslider");
		ui_interface->addVerticalSlider("Ext Input", &fVslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Signal Parameters");
		ui_interface->declare(0, "0", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "style", "hslider");
		ui_interface->declare(&fHslider0, "tooltip", "Sawtooth waveform amplitude");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Mix Amplitude", &fHslider0, -20.0f, -120.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "style", "hslider");
		ui_interface->declare(&fHslider1, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fHslider1, "unit", "PK");
		ui_interface->addHorizontalSlider("Frequency", &fHslider1, 49.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->declare(&fVslider3, "3", "");
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "tooltip", "Percentage frequency-shift up or down for second oscillator");
		ui_interface->declare(&fVslider3, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 1", &fVslider3, -0.100000001f, -10.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fVslider4, "4", "");
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->declare(&fVslider4, "tooltip", "Percentage frequency-shift up or down for third detuned oscillator");
		ui_interface->declare(&fVslider4, "unit", "%%");
		ui_interface->addVerticalSlider("Detuning 2", &fVslider4, 0.100000001f, -10.0f, 10.0f, 0.00999999978f);
		ui_interface->declare(&fVslider2, "5", "");
		ui_interface->declare(&fVslider2, "scale", "log");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fVslider2, "unit", "sec");
		ui_interface->addVerticalSlider("Portamento", &fVslider2, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f);
		ui_interface->declare(&fEntry0, "6", "");
		ui_interface->declare(&fEntry0, "tooltip", "Order of sawtooth aliasing  suppression");
		ui_interface->addNumEntry("Saw Order", &fEntry0, 2.0f, 1.0f, 4.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fVslider0);
		float fSlow1 = (0.00100000005f * std::pow(10.0f, (0.0500000007f * float(fHslider0))));
		float fSlow2 = (0.333333343f * float(fVslider1));
		int iSlow3 = int((float(fEntry0) + -1.0f));
		int iSlow4 = (iSlow3 >= 2);
		int iSlow5 = (iSlow3 >= 1);
		float fSlow6 = std::exp((0.0f - (fConst1 / float(fVslider2))));
		float fSlow7 = (440.0f * (std::pow(2.0f, (0.0833333358f * (float(fHslider1) + -49.0f))) * (1.0f - fSlow6)));
		int iSlow8 = (iSlow3 >= 3);
		float fSlow9 = (1.0f - (0.00999999978f * float(fVslider3)));
		float fSlow10 = ((0.00999999978f * float(fVslider4)) + 1.0f);
		float fSlow11 = (fConst5 * float(fVslider5));
		float fSlow12 = (fConst7 * float(fVslider6));
		float fSlow13 = (fConst0 * float(fVslider7));
		float fSlow14 = float(fCheckbox0);
		float fSlow15 = (fConst8 * fSlow14);
		float fSlow16 = (0.00999999978f * float(fVslider8));
		float fSlow17 = (0.0833333358f * (1.0f - fSlow14));
		float fSlow18 = float(fVslider9);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = (fSlow1 + (0.999000013f * fRec0[1]));
			fRec2[0] = (fSlow7 + (fSlow6 * fRec2[1]));
			float fTemp0 = std::max<float>(20.0f, std::fabs(fRec2[0]));
			fVec1[0] = fTemp0;
			float fTemp1 = (fRec1[1] + (fConst1 * fVec1[1]));
			fRec1[0] = (fTemp1 - std::floor(fTemp1));
			float fTemp2 = (2.0f * fRec1[0]);
			float fTemp3 = (fTemp2 + -1.0f);
			float fTemp4 = float(iVec0[1]);
			float fTemp5 = mydsp_faustpower2_f(fTemp3);
			fVec2[0] = fTemp5;
			float fTemp6 = float(iVec0[2]);
			float fTemp7 = mydsp_faustpower3_f(fTemp3);
			fVec3[0] = (fTemp7 + (1.0f - fTemp2));
			float fTemp8 = ((fTemp7 + (1.0f - (fTemp2 + fVec3[1]))) / fTemp0);
			fVec4[0] = fTemp8;
			float fTemp9 = float(iVec0[3]);
			float fTemp10 = (fTemp5 * (fTemp5 + -2.0f));
			fVec5[0] = fTemp10;
			float fTemp11 = ((fTemp10 - fVec5[1]) / fTemp0);
			fVec6[0] = fTemp11;
			float fTemp12 = ((fTemp11 - fVec6[1]) / fTemp0);
			fVec7[0] = fTemp12;
			float fTemp13 = (fSlow9 * fRec2[0]);
			float fTemp14 = std::max<float>(20.0f, std::fabs(fTemp13));
			fVec8[0] = fTemp14;
			float fTemp15 = (fRec3[1] + (fConst1 * fVec8[1]));
			fRec3[0] = (fTemp15 - std::floor(fTemp15));
			float fTemp16 = (2.0f * fRec3[0]);
			float fTemp17 = (fTemp16 + -1.0f);
			float fTemp18 = mydsp_faustpower2_f(fTemp17);
			fVec9[0] = fTemp18;
			float fTemp19 = mydsp_faustpower3_f(fTemp17);
			fVec10[0] = (fTemp19 + (1.0f - fTemp16));
			float fTemp20 = ((fTemp19 + (1.0f - (fTemp16 + fVec10[1]))) / fTemp14);
			fVec11[0] = fTemp20;
			float fTemp21 = (fTemp18 * (fTemp18 + -2.0f));
			fVec12[0] = fTemp21;
			float fTemp22 = ((fTemp21 - fVec12[1]) / fTemp14);
			fVec13[0] = fTemp22;
			float fTemp23 = ((fTemp22 - fVec13[1]) / fTemp14);
			fVec14[0] = fTemp23;
			float fTemp24 = (fSlow10 * fRec2[0]);
			float fTemp25 = std::max<float>(20.0f, std::fabs(fTemp24));
			fVec15[0] = fTemp25;
			float fTemp26 = (fRec4[1] + (fConst1 * fVec15[1]));
			fRec4[0] = (fTemp26 - std::floor(fTemp26));
			float fTemp27 = (2.0f * fRec4[0]);
			float fTemp28 = (fTemp27 + -1.0f);
			float fTemp29 = mydsp_faustpower2_f(fTemp28);
			fVec16[0] = fTemp29;
			float fTemp30 = mydsp_faustpower3_f(fTemp28);
			fVec17[0] = (fTemp30 + (1.0f - fTemp27));
			float fTemp31 = ((fTemp30 + (1.0f - (fTemp27 + fVec17[1]))) / fTemp25);
			fVec18[0] = fTemp31;
			float fTemp32 = (fTemp29 * (fTemp29 + -2.0f));
			fVec19[0] = fTemp32;
			float fTemp33 = ((fTemp32 - fVec19[1]) / fTemp25);
			fVec20[0] = fTemp33;
			float fTemp34 = ((fTemp33 - fVec20[1]) / fTemp25);
			fVec21[0] = fTemp34;
			float fTemp35 = std::max<float>(fRec2[0], 23.4489498f);
			float fTemp36 = std::max<float>(20.0f, std::fabs(fTemp35));
			fVec22[0] = fTemp36;
			float fTemp37 = (fRec5[1] + (fConst1 * fVec22[1]));
			fRec5[0] = (fTemp37 - std::floor(fTemp37));
			float fTemp38 = (2.0f * fRec5[0]);
			float fTemp39 = (fTemp38 + -1.0f);
			float fTemp40 = mydsp_faustpower2_f(fTemp39);
			fVec23[0] = fTemp40;
			float fTemp41 = ((fTemp4 * (fTemp40 - fVec23[1])) / fTemp36);
			fVec24[(IOTA & 4095)] = fTemp41;
			float fTemp42 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst6 / fTemp35)));
			int iTemp43 = int(fTemp42);
			float fTemp44 = std::floor(fTemp42);
			float fTemp45 = ((fTemp41 - (fVec24[((IOTA - iTemp43) & 4095)] * (fTemp44 + (1.0f - fTemp42)))) - ((fTemp42 - fTemp44) * fVec24[((IOTA - (iTemp43 + 1)) & 4095)]));
			float fTemp46 = std::max<float>(fTemp13, 23.4489498f);
			float fTemp47 = std::max<float>(20.0f, std::fabs(fTemp46));
			fVec25[0] = fTemp47;
			float fTemp48 = (fRec6[1] + (fConst1 * fVec25[1]));
			fRec6[0] = (fTemp48 - std::floor(fTemp48));
			float fTemp49 = (2.0f * fRec6[0]);
			float fTemp50 = (fTemp49 + -1.0f);
			float fTemp51 = mydsp_faustpower2_f(fTemp50);
			fVec26[0] = fTemp51;
			float fTemp52 = ((fTemp4 * (fTemp51 - fVec26[1])) / fTemp47);
			fVec27[(IOTA & 4095)] = fTemp52;
			float fTemp53 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst6 / fTemp46)));
			int iTemp54 = int(fTemp53);
			float fTemp55 = std::floor(fTemp53);
			float fTemp56 = ((fTemp52 - (fVec27[((IOTA - iTemp54) & 4095)] * (fTemp55 + (1.0f - fTemp53)))) - ((fTemp53 - fTemp55) * fVec27[((IOTA - (iTemp54 + 1)) & 4095)]));
			float fTemp57 = std::max<float>(fTemp24, 23.4489498f);
			float fTemp58 = std::max<float>(20.0f, std::fabs(fTemp57));
			fVec28[0] = fTemp58;
			float fTemp59 = (fRec7[1] + (fConst1 * fVec28[1]));
			fRec7[0] = (fTemp59 - std::floor(fTemp59));
			float fTemp60 = (2.0f * fRec7[0]);
			float fTemp61 = (fTemp60 + -1.0f);
			float fTemp62 = mydsp_faustpower2_f(fTemp61);
			fVec29[0] = fTemp62;
			float fTemp63 = ((fTemp4 * (fTemp62 - fVec29[1])) / fTemp58);
			fVec30[(IOTA & 4095)] = fTemp63;
			float fTemp64 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst6 / fTemp57)));
			int iTemp65 = int(fTemp64);
			float fTemp66 = std::floor(fTemp64);
			float fTemp67 = ((fTemp63 - (fVec30[((IOTA - iTemp65) & 4095)] * (fTemp66 + (1.0f - fTemp64)))) - ((fTemp64 - fTemp66) * fVec30[((IOTA - (iTemp65 + 1)) & 4095)]));
			fRec8[0] = ((fConst2 * fTemp45) + (0.999000013f * fRec8[1]));
			fRec9[0] = ((fConst2 * fTemp56) + (0.999000013f * fRec9[1]));
			fRec10[0] = ((fConst2 * fTemp67) + (0.999000013f * fRec10[1]));
			float fTemp68 = mydsp_faustpower3_f(fTemp39);
			fVec31[0] = (fTemp68 + (1.0f - fTemp38));
			float fTemp69 = ((fTemp68 + (1.0f - (fTemp38 + fVec31[1]))) / fTemp36);
			fVec32[0] = fTemp69;
			float fTemp70 = ((fTemp6 * (fTemp69 - fVec32[1])) / fTemp36);
			fVec33[(IOTA & 4095)] = fTemp70;
			fRec11[0] = (fSlow16 + (0.99000001f * fRec11[1]));
			float fTemp71 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst0 * (fRec11[0] / fTemp35))));
			int iTemp72 = int(fTemp71);
			float fTemp73 = std::floor(fTemp71);
			float fTemp74 = (fTemp73 + (1.0f - fTemp71));
			float fTemp75 = (fTemp71 - fTemp73);
			int iTemp76 = (iTemp72 + 1);
			float fTemp77 = mydsp_faustpower3_f(fTemp50);
			fVec34[0] = (fTemp77 + (1.0f - fTemp49));
			float fTemp78 = ((fTemp77 + (1.0f - (fTemp49 + fVec34[1]))) / fTemp47);
			fVec35[0] = fTemp78;
			float fTemp79 = ((fTemp6 * (fTemp78 - fVec35[1])) / fTemp47);
			fVec36[(IOTA & 4095)] = fTemp79;
			float fTemp80 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst0 * (fRec11[0] / fTemp46))));
			int iTemp81 = int(fTemp80);
			float fTemp82 = std::floor(fTemp80);
			float fTemp83 = (fTemp82 + (1.0f - fTemp80));
			float fTemp84 = (fTemp80 - fTemp82);
			int iTemp85 = (iTemp81 + 1);
			float fTemp86 = mydsp_faustpower3_f(fTemp61);
			fVec37[0] = (fTemp86 + (1.0f - fTemp60));
			float fTemp87 = ((fTemp86 + (1.0f - (fTemp60 + fVec37[1]))) / fTemp58);
			fVec38[0] = fTemp87;
			float fTemp88 = ((fTemp6 * (fTemp87 - fVec38[1])) / fTemp58);
			fVec39[(IOTA & 4095)] = fTemp88;
			float fTemp89 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst0 * (fRec11[0] / fTemp57))));
			int iTemp90 = int(fTemp89);
			float fTemp91 = std::floor(fTemp89);
			float fTemp92 = (fTemp91 + (1.0f - fTemp89));
			float fTemp93 = (fTemp89 - fTemp91);
			int iTemp94 = (iTemp90 + 1);
			iRec13[0] = ((1103515245 * iRec13[1]) + 12345);
			fRec12[0] = (((0.522189379f * fRec12[3]) + ((4.65661287e-10f * float(iRec13[0])) + (2.49495602f * fRec12[1]))) - (2.0172658f * fRec12[2]));
			output0[i] = FAUSTFLOAT(((fSlow0 * float(input0[i])) + (fRec0[0] * (((((fSlow2 * (((iSlow4 ? (iSlow8 ? (fConst4 * ((fTemp9 * (fTemp12 - fVec7[1])) / fTemp0)) : (fConst3 * ((fTemp6 * (fTemp8 - fVec4[1])) / fTemp0))) : (iSlow5 ? (fConst2 * ((fTemp4 * (fTemp5 - fVec2[1])) / fTemp0)) : fTemp3)) + (iSlow4 ? (iSlow8 ? (fConst4 * ((fTemp9 * (fTemp23 - fVec14[1])) / fTemp14)) : (fConst3 * ((fTemp6 * (fTemp20 - fVec11[1])) / fTemp14))) : (iSlow5 ? (fConst2 * ((fTemp4 * (fTemp18 - fVec9[1])) / fTemp14)) : fTemp17))) + (iSlow4 ? (iSlow8 ? (fConst4 * ((fTemp9 * (fTemp34 - fVec21[1])) / fTemp25)) : (fConst3 * ((fTemp6 * (fTemp31 - fVec18[1])) / fTemp25))) : (iSlow5 ? (fConst2 * ((fTemp4 * (fTemp29 - fVec16[1])) / fTemp25)) : fTemp28)))) + (fSlow11 * ((fTemp45 + fTemp56) + fTemp67))) + (fSlow12 * (fRec2[0] * ((fRec8[0] + (fSlow9 * fRec9[0])) + (fSlow10 * fRec10[0]))))) + (fSlow13 * ((fSlow15 * ((((fTemp70 - (fVec33[((IOTA - iTemp72) & 4095)] * fTemp74)) - (fTemp75 * fVec33[((IOTA - iTemp76) & 4095)])) + ((fTemp79 - (fVec36[((IOTA - iTemp81) & 4095)] * fTemp83)) - (fTemp84 * fVec36[((IOTA - iTemp85) & 4095)]))) + ((fTemp88 - (fVec39[((IOTA - iTemp90) & 4095)] * fTemp92)) - (fTemp93 * fVec39[((IOTA - iTemp94) & 4095)])))) + (fSlow17 * ((((fTemp41 - (fTemp74 * fVec24[((IOTA - iTemp72) & 4095)])) - (fTemp75 * fVec24[((IOTA - iTemp76) & 4095)])) + ((fTemp52 - (fTemp83 * fVec27[((IOTA - iTemp81) & 4095)])) - (fTemp84 * fVec27[((IOTA - iTemp85) & 4095)]))) + ((fTemp63 - (fTemp92 * fVec30[((IOTA - iTemp90) & 4095)])) - (fTemp93 * fVec30[((IOTA - iTemp94) & 4095)]))))))) + (fSlow18 * (((0.0499220341f * fRec12[0]) + (0.0506126992f * fRec12[2])) - ((0.0959935337f * fRec12[1]) + (0.00440878607f * fRec12[3]))))))));
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
			}
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fVec1[1] = fVec1[0];
			fRec1[1] = fRec1[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fRec3[1] = fRec3[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fRec4[1] = fRec4[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			fVec19[1] = fVec19[0];
			fVec20[1] = fVec20[0];
			fVec21[1] = fVec21[0];
			fVec22[1] = fVec22[0];
			fRec5[1] = fRec5[0];
			fVec23[1] = fVec23[0];
			IOTA = (IOTA + 1);
			fVec25[1] = fVec25[0];
			fRec6[1] = fRec6[0];
			fVec26[1] = fVec26[0];
			fVec28[1] = fVec28[0];
			fRec7[1] = fRec7[0];
			fVec29[1] = fVec29[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fVec31[1] = fVec31[0];
			fVec32[1] = fVec32[0];
			fRec11[1] = fRec11[0];
			fVec34[1] = fVec34[0];
			fVec35[1] = fVec35[0];
			fVec37[1] = fVec37[0];
			fVec38[1] = fVec38[0];
			iRec13[1] = iRec13[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec12[j1] = fRec12[(j1 - 1)];
			}
		}
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

//#define A1S_BOARD true                  //uncomment for Ai-thinker A1S board

#define MULT_S32 2147483647
#define DIV_S32 4.6566129e-10
#define clip(sample) std::max(-MULT_S32, std::min(MULT_S32, ((int32_t)(sample * MULT_S32))));

VirtualAnalogSynth::VirtualAnalogSynth(int sample_rate, int buffer_size)
{
    fBS = buffer_size;
    fDSP = new mydsp();
    fDSP->init(sample_rate);
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);
    fHandle = NULL;
    
    i2s_pin_config_t pin_config;
#if TTGO_TAUDIO
    pin_config = {
        .bck_io_num = 33,
        .ws_io_num = 25,
        .data_out_num = 26,
        .data_in_num = 27
    };
#elif A1S_BOARD
    pin_config = {
        .bck_io_num = 27,
        .ws_io_num = 26,
        .data_out_num = 25,
        .data_in_num = 35
    };
#else // Default
    pin_config = {
        .bck_io_num = 33,
        .ws_io_num = 25,
        .data_out_num = 26,
        .data_in_num = 27
    };
#endif
    configureI2S(sample_rate, buffer_size, pin_config);
    
    if (fDSP->getNumInputs() > 0) {
        fInChannel = new float*[fDSP->getNumInputs()];
        for (int i = 0; i < fDSP->getNumInputs(); i++) {
            fInChannel[i] = new float[fBS];
        }
    }
    if (fDSP->getNumOutputs() > 0) {
        fOutChannel = new float*[fDSP->getNumOutputs()];
        for (int i = 0; i < fDSP->getNumOutputs(); i++) {
            fOutChannel[i] = new float[fBS];
        }
    }
}

VirtualAnalogSynth::~VirtualAnalogSynth()
{
    for (int i = 0; i < fDSP->getNumInputs(); i++) {
        delete[] fInChannel[i];
    }
    delete [] fInChannel;
    
    for (int i = 0; i < fDSP->getNumOutputs(); i++) {
        delete[] fOutChannel[i];
    }
    delete [] fOutChannel;
    
    delete fDSP;
    delete fUI;
}

bool VirtualAnalogSynth::start()
{
    xTaskCreate(audioTaskHandler, "Faust DSP Task", 1024, (void*)this, 5, &fHandle);
    return true;
}

void VirtualAnalogSynth::stop()
{
    if (fHandle != NULL) {
        vTaskDelete(fHandle);
        fHandle = NULL;
    }
}

void VirtualAnalogSynth::setParamValue(const std::string& path, float value)
{
    fUI->setParamValue(path, value);
}

void VirtualAnalogSynth::configureI2S(int sample_rate, int buffer_size, i2s_pin_config_t pin_config)
{
    #if A1S_BOARD
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
        .sample_rate = sample_rate,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // high interrupt priority
        .dma_buf_count = 3,
        .dma_buf_len = buffer_size,
        .use_apll = true
    };
    #else // default
        i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
        .sample_rate = sample_rate,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // high interrupt priority
        .dma_buf_count = 3,
        .dma_buf_len = buffer_size,
        .use_apll = false
    };
    #endif
    i2s_driver_install((i2s_port_t)0, &i2s_config, 0, NULL);
    i2s_set_pin((i2s_port_t)0, &pin_config);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0_CLK_OUT1);
    REG_WRITE(PIN_CTRL, 0xFFFFFFF0);
}

void VirtualAnalogSynth::audioTask()
{
    while (true) {
        if (fDSP->getNumInputs() > 0) {
            
            // Read from the card
            int32_t samples_data_in[2*fBS];
            size_t bytes_read = 0;
            i2s_read((i2s_port_t)0, &samples_data_in, 8*fBS, &bytes_read, portMAX_DELAY);
            
            // Convert and copy inputs
            if (fDSP->getNumInputs() == 2) { // if stereo
                for (int i = 0; i < fBS; i++) {
                    fInChannel[0][i] = (float)samples_data_in[i*2]*DIV_S32;
                    fInChannel[1][i] = (float)samples_data_in[i*2+1]*DIV_S32;
                }
            } else {
                for (int i = 0; i < fBS; i++) {
                    fInChannel[0][i] = (float)samples_data_in[i*2]*DIV_S32;
                }
            }
        }
        
        // Call DSP
        fDSP->compute(fBS, fInChannel, fOutChannel);
        
        // Convert and copy outputs
        int32_t samples_data_out[2*fBS];
        if (fDSP->getNumOutputs() == 2) {
            // if stereo
            for (int i = 0; i < fBS; i++) {
                samples_data_out[i*2] = clip(fOutChannel[0][i]);
                samples_data_out[i*2+1] = clip(fOutChannel[1][i]);
            }
        } else {
            // otherwise only first channel
            for (int i = 0; i < fBS; i++) {
                samples_data_out[i*2] = clip(fOutChannel[0][i]);
                samples_data_out[i*2+1] = samples_data_out[i*2];
            }
        }
        
        // Write to the card
        size_t bytes_writen = 0;
        i2s_write((i2s_port_t)0, &samples_data_out, 8*fBS, &bytes_writen, portMAX_DELAY);
    }
}

void VirtualAnalogSynth::audioTaskHandler(void* arg)
{
    VirtualAnalogSynth* audio = (VirtualAnalogSynth*)arg;
    audio->audioTask();
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

#endif

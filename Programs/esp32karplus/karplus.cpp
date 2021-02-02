/* ------------------------------------------------------------
author: "Yann Orlarey"
name: "Kisana"
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

#include "karplus.h"

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

class mydspSIG0 {
	
  private:
	
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	int getInputRatemydspSIG0(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	int getOutputRatemydspSIG0(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i = 0; (i < count); i = (i + 1)) {
			table[i] = 0.0f;
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	float ftbl0[16];
	FAUSTFLOAT fHslider1;
	float fVec0[2];
	int iVec1[2];
	int fSampleRate;
	float fConst0;
	int iConst1;
	int iRec1[2];
	int iVec2[2];
	float fRec2[2];
	int iRec3[2];
	int iRec4[2];
	float ftbl1[16];
	FAUSTFLOAT fVslider0;
	int iVec3[2];
	int iConst2;
	int iRec6[2];
	int iVec4[2];
	int iRec7[2];
	int iRec8[2];
	int iVec5[2];
	float fRec5[2];
	int IOTA;
	float fVec6[256];
	float fRec0[3];
	int iVec7[2];
	float fRec10[2];
	float fVec8[256];
	float fRec9[3];
	float ftbl2[16];
	FAUSTFLOAT fVslider1;
	int iVec9[2];
	int iConst3;
	int iRec13[2];
	int iVec10[2];
	int iRec14[2];
	int iRec15[2];
	int iVec11[2];
	float fRec12[2];
	float fVec12[128];
	float fRec11[3];
	int iVec13[2];
	float fRec17[2];
	float fVec14[128];
	float fRec16[3];
	int iVec15[2];
	float fRec19[2];
	float fVec16[256];
	float fRec18[3];
	int iVec17[2];
	float fRec21[2];
	float fVec18[256];
	float fRec20[3];
	int iVec19[2];
	float fRec23[2];
	float fVec20[128];
	float fRec22[3];
	int iVec21[2];
	float fRec25[2];
	float fVec22[128];
	float fRec24[3];
	int iVec23[2];
	float fRec27[2];
	float fVec24[512];
	float fRec26[3];
	int iVec25[2];
	float fRec29[2];
	float fVec26[128];
	float fRec28[3];
	int iVec27[2];
	float fRec31[2];
	float fVec28[256];
	float fRec30[3];
	int iVec29[2];
	float fRec33[2];
	float fVec30[64];
	float fRec32[3];
	int iVec31[2];
	float fRec35[2];
	float fVec32[512];
	float fRec34[3];
	int iVec33[2];
	float fRec37[2];
	float fVec34[128];
	float fRec36[3];
	int iVec35[2];
	float fRec39[2];
	float fVec36[256];
	float fRec38[3];
	int iVec37[2];
	float fRec41[2];
	float fVec38[64];
	float fRec40[3];
	int iVec39[2];
	float fRec43[2];
	float fVec40[256];
	float fRec42[3];
	int iVec41[2];
	float fRec45[2];
	float fVec42[128];
	float fRec44[3];
	int iVec43[2];
	float fRec47[2];
	float fVec44[512];
	float fRec46[3];
	int iVec45[2];
	float fRec49[2];
	float fVec46[128];
	float fRec48[3];
	int iVec47[2];
	float fRec51[2];
	float fVec48[256];
	float fRec50[3];
	int iVec49[2];
	float fRec53[2];
	float fVec50[64];
	float fRec52[3];
	float ftbl3[16];
	FAUSTFLOAT fVslider2;
	int iVec51[2];
	int iConst4;
	int iRec56[2];
	int iVec52[2];
	int iRec57[2];
	int iRec58[2];
	int iVec53[2];
	float fRec55[2];
	float fVec54[128];
	float fRec54[3];
	int iVec55[2];
	float fRec60[2];
	float fVec56[128];
	float fRec59[3];
	int iVec57[2];
	float fRec62[2];
	float fVec58[128];
	float fRec61[3];
	int iVec59[2];
	float fRec64[2];
	float fVec60[64];
	float fRec63[3];
	int iVec61[2];
	float fRec66[2];
	float fVec62[64];
	float fRec65[3];
	int iVec63[2];
	float fRec68[2];
	float fVec64[64];
	float fRec67[3];
	int iVec65[2];
	float fRec70[2];
	float fVec66[64];
	float fRec69[3];
	int iVec67[2];
	float fRec72[2];
	float fVec68[64];
	float fRec71[3];
	int iVec69[2];
	float fRec74[2];
	float fVec70[32];
	float fRec73[3];
	int iVec71[2];
	float fRec76[2];
	float fVec72[32];
	float fRec75[3];
	int iVec73[2];
	float fRec78[2];
	float fVec74[32];
	float fRec77[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Yann Orlarey");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("filename", "karplus.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "Kisana");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
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
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(16, ftbl0);
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		iConst1 = int((0.166666672f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(16, ftbl1);
		iConst2 = int((0.5f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(16, ftbl2);
		iConst3 = int((0.25f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(16, ftbl3);
		iConst4 = int((0.125f * fConst0));
		deletemydspSIG0(sig0);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(4.0f);
		fHslider1 = FAUSTFLOAT(0.20000000000000001f);
		fVslider0 = FAUSTFLOAT(0.0f);
		fVslider1 = FAUSTFLOAT(2.0f);
		fVslider2 = FAUSTFLOAT(4.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec1[l1] = 0;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec1[l2] = 0;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			iVec2[l3] = 0;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec2[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			iRec3[l5] = 0;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			iRec4[l6] = 0;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			iVec3[l7] = 0;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			iRec6[l8] = 0;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			iVec4[l9] = 0;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			iRec7[l10] = 0;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			iRec8[l11] = 0;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			iVec5[l12] = 0;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec5[l13] = 0.0f;
		}
		IOTA = 0;
		for (int l14 = 0; (l14 < 256); l14 = (l14 + 1)) {
			fVec6[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
			fRec0[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			iVec7[l16] = 0;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec10[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 256); l18 = (l18 + 1)) {
			fVec8[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
			fRec9[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			iVec9[l20] = 0;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			iRec13[l21] = 0;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			iVec10[l22] = 0;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			iRec14[l23] = 0;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			iRec15[l24] = 0;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			iVec11[l25] = 0;
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec12[l26] = 0.0f;
		}
		for (int l27 = 0; (l27 < 128); l27 = (l27 + 1)) {
			fVec12[l27] = 0.0f;
		}
		for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			fRec11[l28] = 0.0f;
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			iVec13[l29] = 0;
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec17[l30] = 0.0f;
		}
		for (int l31 = 0; (l31 < 128); l31 = (l31 + 1)) {
			fVec14[l31] = 0.0f;
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec16[l32] = 0.0f;
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			iVec15[l33] = 0;
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec19[l34] = 0.0f;
		}
		for (int l35 = 0; (l35 < 256); l35 = (l35 + 1)) {
			fVec16[l35] = 0.0f;
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec18[l36] = 0.0f;
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			iVec17[l37] = 0;
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec21[l38] = 0.0f;
		}
		for (int l39 = 0; (l39 < 256); l39 = (l39 + 1)) {
			fVec18[l39] = 0.0f;
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec20[l40] = 0.0f;
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			iVec19[l41] = 0;
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec23[l42] = 0.0f;
		}
		for (int l43 = 0; (l43 < 128); l43 = (l43 + 1)) {
			fVec20[l43] = 0.0f;
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec22[l44] = 0.0f;
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			iVec21[l45] = 0;
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec25[l46] = 0.0f;
		}
		for (int l47 = 0; (l47 < 128); l47 = (l47 + 1)) {
			fVec22[l47] = 0.0f;
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec24[l48] = 0.0f;
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			iVec23[l49] = 0;
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec27[l50] = 0.0f;
		}
		for (int l51 = 0; (l51 < 512); l51 = (l51 + 1)) {
			fVec24[l51] = 0.0f;
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec26[l52] = 0.0f;
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			iVec25[l53] = 0;
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec29[l54] = 0.0f;
		}
		for (int l55 = 0; (l55 < 128); l55 = (l55 + 1)) {
			fVec26[l55] = 0.0f;
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec28[l56] = 0.0f;
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			iVec27[l57] = 0;
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec31[l58] = 0.0f;
		}
		for (int l59 = 0; (l59 < 256); l59 = (l59 + 1)) {
			fVec28[l59] = 0.0f;
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec30[l60] = 0.0f;
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			iVec29[l61] = 0;
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec33[l62] = 0.0f;
		}
		for (int l63 = 0; (l63 < 64); l63 = (l63 + 1)) {
			fVec30[l63] = 0.0f;
		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec32[l64] = 0.0f;
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			iVec31[l65] = 0;
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec35[l66] = 0.0f;
		}
		for (int l67 = 0; (l67 < 512); l67 = (l67 + 1)) {
			fVec32[l67] = 0.0f;
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec34[l68] = 0.0f;
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			iVec33[l69] = 0;
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec37[l70] = 0.0f;
		}
		for (int l71 = 0; (l71 < 128); l71 = (l71 + 1)) {
			fVec34[l71] = 0.0f;
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec36[l72] = 0.0f;
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			iVec35[l73] = 0;
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec39[l74] = 0.0f;
		}
		for (int l75 = 0; (l75 < 256); l75 = (l75 + 1)) {
			fVec36[l75] = 0.0f;
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec38[l76] = 0.0f;
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			iVec37[l77] = 0;
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			fRec41[l78] = 0.0f;
		}
		for (int l79 = 0; (l79 < 64); l79 = (l79 + 1)) {
			fVec38[l79] = 0.0f;
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec40[l80] = 0.0f;
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			iVec39[l81] = 0;
		}
		for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			fRec43[l82] = 0.0f;
		}
		for (int l83 = 0; (l83 < 256); l83 = (l83 + 1)) {
			fVec40[l83] = 0.0f;
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec42[l84] = 0.0f;
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			iVec41[l85] = 0;
		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			fRec45[l86] = 0.0f;
		}
		for (int l87 = 0; (l87 < 128); l87 = (l87 + 1)) {
			fVec42[l87] = 0.0f;
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec44[l88] = 0.0f;
		}
		for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			iVec43[l89] = 0;
		}
		for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			fRec47[l90] = 0.0f;
		}
		for (int l91 = 0; (l91 < 512); l91 = (l91 + 1)) {
			fVec44[l91] = 0.0f;
		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec46[l92] = 0.0f;
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			iVec45[l93] = 0;
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fRec49[l94] = 0.0f;
		}
		for (int l95 = 0; (l95 < 128); l95 = (l95 + 1)) {
			fVec46[l95] = 0.0f;
		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec48[l96] = 0.0f;
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			iVec47[l97] = 0;
		}
		for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			fRec51[l98] = 0.0f;
		}
		for (int l99 = 0; (l99 < 256); l99 = (l99 + 1)) {
			fVec48[l99] = 0.0f;
		}
		for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			fRec50[l100] = 0.0f;
		}
		for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			iVec49[l101] = 0;
		}
		for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			fRec53[l102] = 0.0f;
		}
		for (int l103 = 0; (l103 < 64); l103 = (l103 + 1)) {
			fVec50[l103] = 0.0f;
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec52[l104] = 0.0f;
		}
		for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			iVec51[l105] = 0;
		}
		for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			iRec56[l106] = 0;
		}
		for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			iVec52[l107] = 0;
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			iRec57[l108] = 0;
		}
		for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			iRec58[l109] = 0;
		}
		for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			iVec53[l110] = 0;
		}
		for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			fRec55[l111] = 0.0f;
		}
		for (int l112 = 0; (l112 < 128); l112 = (l112 + 1)) {
			fVec54[l112] = 0.0f;
		}
		for (int l113 = 0; (l113 < 3); l113 = (l113 + 1)) {
			fRec54[l113] = 0.0f;
		}
		for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			iVec55[l114] = 0;
		}
		for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			fRec60[l115] = 0.0f;
		}
		for (int l116 = 0; (l116 < 128); l116 = (l116 + 1)) {
			fVec56[l116] = 0.0f;
		}
		for (int l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			fRec59[l117] = 0.0f;
		}
		for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			iVec57[l118] = 0;
		}
		for (int l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			fRec62[l119] = 0.0f;
		}
		for (int l120 = 0; (l120 < 128); l120 = (l120 + 1)) {
			fVec58[l120] = 0.0f;
		}
		for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			fRec61[l121] = 0.0f;
		}
		for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			iVec59[l122] = 0;
		}
		for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			fRec64[l123] = 0.0f;
		}
		for (int l124 = 0; (l124 < 64); l124 = (l124 + 1)) {
			fVec60[l124] = 0.0f;
		}
		for (int l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			fRec63[l125] = 0.0f;
		}
		for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			iVec61[l126] = 0;
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fRec66[l127] = 0.0f;
		}
		for (int l128 = 0; (l128 < 64); l128 = (l128 + 1)) {
			fVec62[l128] = 0.0f;
		}
		for (int l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			fRec65[l129] = 0.0f;
		}
		for (int l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			iVec63[l130] = 0;
		}
		for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) {
			fRec68[l131] = 0.0f;
		}
		for (int l132 = 0; (l132 < 64); l132 = (l132 + 1)) {
			fVec64[l132] = 0.0f;
		}
		for (int l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			fRec67[l133] = 0.0f;
		}
		for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			iVec65[l134] = 0;
		}
		for (int l135 = 0; (l135 < 2); l135 = (l135 + 1)) {
			fRec70[l135] = 0.0f;
		}
		for (int l136 = 0; (l136 < 64); l136 = (l136 + 1)) {
			fVec66[l136] = 0.0f;
		}
		for (int l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			fRec69[l137] = 0.0f;
		}
		for (int l138 = 0; (l138 < 2); l138 = (l138 + 1)) {
			iVec67[l138] = 0;
		}
		for (int l139 = 0; (l139 < 2); l139 = (l139 + 1)) {
			fRec72[l139] = 0.0f;
		}
		for (int l140 = 0; (l140 < 64); l140 = (l140 + 1)) {
			fVec68[l140] = 0.0f;
		}
		for (int l141 = 0; (l141 < 3); l141 = (l141 + 1)) {
			fRec71[l141] = 0.0f;
		}
		for (int l142 = 0; (l142 < 2); l142 = (l142 + 1)) {
			iVec69[l142] = 0;
		}
		for (int l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			fRec74[l143] = 0.0f;
		}
		for (int l144 = 0; (l144 < 32); l144 = (l144 + 1)) {
			fVec70[l144] = 0.0f;
		}
		for (int l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			fRec73[l145] = 0.0f;
		}
		for (int l146 = 0; (l146 < 2); l146 = (l146 + 1)) {
			iVec71[l146] = 0;
		}
		for (int l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			fRec76[l147] = 0.0f;
		}
		for (int l148 = 0; (l148 < 32); l148 = (l148 + 1)) {
			fVec72[l148] = 0.0f;
		}
		for (int l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			fRec75[l149] = 0.0f;
		}
		for (int l150 = 0; (l150 < 2); l150 = (l150 + 1)) {
			iVec73[l150] = 0;
		}
		for (int l151 = 0; (l151 < 2); l151 = (l151 + 1)) {
			fRec78[l151] = 0.0f;
		}
		for (int l152 = 0; (l152 < 32); l152 = (l152 + 1)) {
			fVec74[l152] = 0.0f;
		}
		for (int l153 = 0; (l153 < 3); l153 = (l153 + 1)) {
			fRec77[l153] = 0.0f;
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
		ui_interface->openVerticalBox("Kisana");
		ui_interface->openVerticalBox("Kisana");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Instrument Hands");
		ui_interface->declare(&fVslider0, "acc", "1 0 -10 0 14");
		ui_interface->declare(&fVslider0, "unit", "pk");
		ui_interface->addVerticalSlider("1 (Note 48)", &fVslider0, 0.0f, 0.0f, 11.0f, 1.0f);
		ui_interface->declare(&fVslider1, "acc", "1 0 -10 0 14");
		ui_interface->declare(&fVslider1, "unit", "pk");
		ui_interface->addVerticalSlider("2 (Note 60)", &fVslider1, 2.0f, 0.0f, 11.0f, 1.0f);
		ui_interface->declare(&fVslider2, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fVslider2, "unit", "pk");
		ui_interface->addVerticalSlider("3 (Note 72)", &fVslider2, 4.0f, 0.0f, 11.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "acc", "0 1 -10 0 10");
		ui_interface->addHorizontalSlider("Brightness", &fHslider1, 0.200000003f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "acc", "2 1 -10 0 12");
		ui_interface->addHorizontalSlider("Resonance", &fHslider0, 4.0f, 0.100000001f, 10.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		float fSlow1 = (0.5f * std::pow(0.00100000005f, (0.0045454544f / fSlow0)));
		float fSlow2 = float(fHslider1);
		int iSlow3 = (fSlow2 <= 0.0f);
		int iSlow4 = int(float(fVslider0));
		int iSlow5 = (float(iSlow4) <= 0.0f);
		float fSlow6 = (0.5f * std::pow(0.00100000005f, (0.00340524339f / fSlow0)));
		float fSlow7 = (0.5f * std::pow(0.00100000005f, (0.0022727272f / fSlow0)));
		int iSlow8 = int(float(fVslider1));
		int iSlow9 = (float(iSlow8) <= 0.0f);
		float fSlow10 = (0.5f * std::pow(0.00100000005f, (0.0017026217f / fSlow0)));
		float fSlow11 = (0.5f * std::pow(0.00100000005f, (0.00510210032f / fSlow0)));
		float fSlow12 = (0.5f * std::pow(0.00100000005f, (0.00303372694f / fSlow0)));
		float fSlow13 = (0.5f * std::pow(0.00100000005f, (0.00255105016f / fSlow0)));
		float fSlow14 = (0.5f * std::pow(0.00100000005f, (0.00151686347f / fSlow0)));
		float fSlow15 = (0.5f * std::pow(0.00100000005f, (0.00606745388f / fSlow0)));
		float fSlow16 = (0.5f * std::pow(0.00100000005f, (0.00127552508f / fSlow0)));
		float fSlow17 = (0.5f * std::pow(0.00100000005f, (0.00681048678f / fSlow0)));
		float fSlow18 = (0.5f * std::pow(0.00100000005f, (0.0011363636f / fSlow0)));
		float fSlow19 = (0.5f * std::pow(0.00100000005f, (0.00382225635f / fSlow0)));
		float fSlow20 = (0.5f * std::pow(0.00100000005f, (0.00191112817f / fSlow0)));
		float fSlow21 = (0.5f * std::pow(0.00100000005f, (0.00764451269f / fSlow0)));
		float fSlow22 = (0.5f * std::pow(0.00100000005f, (0.000955564086f / fSlow0)));
		int iSlow23 = int(float(fVslider2));
		int iSlow24 = (float(iSlow23) <= 0.0f);
		float fSlow25 = (0.5f * std::pow(0.00100000005f, (0.000851310848f / fSlow0)));
		float fSlow26 = (0.5f * std::pow(0.00100000005f, (0.000758431735f / fSlow0)));
		float fSlow27 = (0.5f * std::pow(0.00100000005f, (0.00063776254f / fSlow0)));
		float fSlow28 = (0.5f * std::pow(0.00100000005f, (0.0005681818f / fSlow0)));
		float fSlow29 = (0.5f * std::pow(0.00100000005f, (0.000477782043f / fSlow0)));
		for (int i = 0; (i < count); i = (i + 1)) {
			fVec0[0] = fSlow2;
			iVec1[0] = 1;
			iRec1[0] = ((iVec1[1] + iRec1[1]) % iConst1);
			int iTemp0 = (iRec1[0] == 0);
			iVec2[0] = iTemp0;
			fRec2[0] = (iVec2[1] ? 0.0f : (fRec2[1] + std::fabs((fSlow2 - fVec0[1]))));
			iRec3[0] = ((iTemp0 + iRec3[1]) % 15);
			ftbl0[((iTemp0 & ((fRec2[0] > 0.0f) | iSlow3)) ? iRec3[0] : 15)] = fSlow2;
			float fTemp1 = ftbl0[iRec3[0]];
			float fTemp2 = (fTemp1 + 1.0f);
			float fTemp3 = (1.0f - fTemp1);
			iRec4[0] = ((1103515245 * iRec4[1]) + 12345);
			float fTemp4 = float(iRec4[0]);
			iVec3[0] = iSlow4;
			iRec6[0] = ((iVec1[1] + iRec6[1]) % iConst2);
			int iTemp5 = (iRec6[0] == 0);
			iVec4[0] = iTemp5;
			iRec7[0] = (iVec4[1] ? 0 : (iRec7[1] + std::abs((iSlow4 - iVec3[1]))));
			iRec8[0] = ((iTemp5 + iRec8[1]) % 15);
			ftbl1[((iTemp5 & ((iRec7[0] > 0) | iSlow5)) ? iRec8[0] : 15)] = float(iSlow4);
			float fTemp6 = ftbl1[iRec8[0]];
			int iTemp7 = (std::fabs((fTemp6 + -5.0f)) < 0.5f);
			iVec5[0] = iTemp7;
			fRec5[0] = ((fRec5[1] + float((float((iTemp7 - iVec5[1])) > 0.0f))) - (0.00498866197f * float((fRec5[1] > 0.0f))));
			fVec6[(IOTA & 255)] = ((fSlow1 * ((fTemp2 * fRec0[1]) + (fTemp3 * fRec0[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec5[0] > 0.0f)))));
			fRec0[0] = fVec6[((IOTA - 199) & 255)];
			int iTemp8 = (std::fabs((fTemp6 + -7.0f)) < 0.5f);
			iVec7[0] = iTemp8;
			fRec10[0] = ((fRec10[1] + float((float((iTemp8 - iVec7[1])) > 0.0f))) - (0.00665906491f * float((fRec10[1] > 0.0f))));
			fVec8[(IOTA & 255)] = ((fSlow6 * ((fTemp2 * fRec9[1]) + (fTemp3 * fRec9[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec10[0] > 0.0f)))));
			fRec9[0] = fVec8[((IOTA - 149) & 255)];
			iVec9[0] = iSlow8;
			iRec13[0] = ((iVec1[1] + iRec13[1]) % iConst3);
			int iTemp9 = (iRec13[0] == 0);
			iVec10[0] = iTemp9;
			iRec14[0] = (iVec10[1] ? 0 : (iRec14[1] + std::abs((iSlow8 - iVec9[1]))));
			iRec15[0] = ((iTemp9 + iRec15[1]) % 15);
			ftbl2[((iTemp9 & ((iRec14[0] > 0) | iSlow9)) ? iRec15[0] : 15)] = float(iSlow8);
			float fTemp10 = ftbl2[iRec15[0]];
			int iTemp11 = (std::fabs((fTemp10 + -5.0f)) < 0.5f);
			iVec11[0] = iTemp11;
			fRec12[0] = ((fRec12[1] + float((float((iTemp11 - iVec11[1])) > 0.0f))) - (0.00997732393f * float((fRec12[1] > 0.0f))));
			fVec12[(IOTA & 127)] = ((fSlow7 * ((fTemp2 * fRec11[1]) + (fTemp3 * fRec11[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec12[0] > 0.0f)))));
			fRec11[0] = fVec12[((IOTA - 99) & 127)];
			int iTemp12 = (std::fabs((fTemp10 + -7.0f)) < 0.5f);
			iVec13[0] = iTemp12;
			fRec17[0] = ((fRec17[1] + float((float((iTemp12 - iVec13[1])) > 0.0f))) - (0.0133181298f * float((fRec17[1] > 0.0f))));
			fVec14[(IOTA & 127)] = ((fSlow10 * ((fTemp2 * fRec16[1]) + (fTemp3 * fRec16[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec17[0] > 0.0f)))));
			fRec16[0] = fVec14[((IOTA - 74) & 127)];
			int iTemp13 = (std::fabs((fTemp6 + -4.0f)) < 0.5f);
			iVec15[0] = iTemp13;
			fRec19[0] = ((fRec19[1] + float((float((iTemp13 - iVec15[1])) > 0.0f))) - (0.00444439286f * float((fRec19[1] > 0.0f))));
			fVec16[(IOTA & 255)] = ((fSlow11 * ((fTemp2 * fRec18[1]) + (fTemp3 * fRec18[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec19[0] > 0.0f)))));
			fRec18[0] = fVec16[((IOTA - 224) & 255)];
			int iTemp14 = (std::fabs((fTemp6 + -8.0f)) < 0.5f);
			iVec17[0] = iTemp14;
			fRec21[0] = ((fRec21[1] + float((float((iTemp14 - iVec17[1])) > 0.0f))) - (0.00747454772f * float((fRec21[1] > 0.0f))));
			fVec18[(IOTA & 255)] = ((fSlow12 * ((fTemp2 * fRec20[1]) + (fTemp3 * fRec20[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec21[0] > 0.0f)))));
			fRec20[0] = fVec18[((IOTA - 132) & 255)];
			int iTemp15 = (std::fabs((fTemp10 + -4.0f)) < 0.5f);
			iVec19[0] = iTemp15;
			fRec23[0] = ((fRec23[1] + float((float((iTemp15 - iVec19[1])) > 0.0f))) - (0.00888878573f * float((fRec23[1] > 0.0f))));
			fVec20[(IOTA & 127)] = ((fSlow13 * ((fTemp2 * fRec22[1]) + (fTemp3 * fRec22[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec23[0] > 0.0f)))));
			fRec22[0] = fVec20[((IOTA - 111) & 127)];
			int iTemp16 = (std::fabs((fTemp10 + -8.0f)) < 0.5f);
			iVec21[0] = iTemp16;
			fRec25[0] = ((fRec25[1] + float((float((iTemp16 - iVec21[1])) > 0.0f))) - (0.0149490954f * float((fRec25[1] > 0.0f))));
			fVec22[(IOTA & 127)] = ((fSlow14 * ((fTemp2 * fRec24[1]) + (fTemp3 * fRec24[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec25[0] > 0.0f)))));
			fRec24[0] = fVec22[((IOTA - 65) & 127)];
			int iTemp17 = (std::fabs((fTemp6 + -3.0f)) < 0.5f);
			iVec23[0] = iTemp17;
			fRec27[0] = ((fRec27[1] + float((float((iTemp17 - iVec23[1])) > 0.0f))) - (0.00373727386f * float((fRec27[1] > 0.0f))));
			fVec24[(IOTA & 511)] = ((fSlow15 * ((fTemp2 * fRec26[1]) + (fTemp3 * fRec26[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec27[0] > 0.0f)))));
			fRec26[0] = fVec24[((IOTA - 266) & 511)];
			int iTemp18 = (std::fabs((fTemp6 + -9.0f)) < 0.5f);
			iVec25[0] = iTemp18;
			fRec29[0] = ((fRec29[1] + float((float((iTemp18 - iVec25[1])) > 0.0f))) - (0.00888878573f * float((fRec29[1] > 0.0f))));
			fVec26[(IOTA & 127)] = ((fSlow13 * ((fTemp2 * fRec28[1]) + (fTemp3 * fRec28[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec29[0] > 0.0f)))));
			fRec28[0] = fVec26[((IOTA - 111) & 127)];
			int iTemp19 = (std::fabs((fTemp10 + -3.0f)) < 0.5f);
			iVec27[0] = iTemp19;
			fRec31[0] = ((fRec31[1] + float((float((iTemp19 - iVec27[1])) > 0.0f))) - (0.00747454772f * float((fRec31[1] > 0.0f))));
			fVec28[(IOTA & 255)] = ((fSlow12 * ((fTemp2 * fRec30[1]) + (fTemp3 * fRec30[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec31[0] > 0.0f)))));
			fRec30[0] = fVec28[((IOTA - 132) & 255)];
			int iTemp20 = (std::fabs((fTemp10 + -9.0f)) < 0.5f);
			iVec29[0] = iTemp20;
			fRec33[0] = ((fRec33[1] + float((float((iTemp20 - iVec29[1])) > 0.0f))) - (0.0177775715f * float((fRec33[1] > 0.0f))));
			fVec30[(IOTA & 63)] = ((fSlow16 * ((fTemp2 * fRec32[1]) + (fTemp3 * fRec32[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec33[0] > 0.0f)))));
			fRec32[0] = fVec30[((IOTA - 55) & 63)];
			int iTemp21 = (std::fabs((fTemp6 + -2.0f)) < 0.5f);
			iVec31[0] = iTemp21;
			fRec35[0] = ((fRec35[1] + float((float((iTemp21 - iVec31[1])) > 0.0f))) - (0.00332953245f * float((fRec35[1] > 0.0f))));
			fVec32[(IOTA & 511)] = ((fSlow17 * ((fTemp2 * fRec34[1]) + (fTemp3 * fRec34[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec35[0] > 0.0f)))));
			fRec34[0] = fVec32[((IOTA - 299) & 511)];
			int iTemp22 = (std::fabs((fTemp6 + -10.0f)) < 0.5f);
			iVec33[0] = iTemp22;
			fRec37[0] = ((fRec37[1] + float((float((iTemp22 - iVec33[1])) > 0.0f))) - (0.00997732393f * float((fRec37[1] > 0.0f))));
			fVec34[(IOTA & 127)] = ((fSlow7 * ((fTemp2 * fRec36[1]) + (fTemp3 * fRec36[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec37[0] > 0.0f)))));
			fRec36[0] = fVec34[((IOTA - 99) & 127)];
			int iTemp23 = (std::fabs((fTemp10 + -2.0f)) < 0.5f);
			iVec35[0] = iTemp23;
			fRec39[0] = ((fRec39[1] + float((float((iTemp23 - iVec35[1])) > 0.0f))) - (0.00665906491f * float((fRec39[1] > 0.0f))));
			fVec36[(IOTA & 255)] = ((fSlow6 * ((fTemp2 * fRec38[1]) + (fTemp3 * fRec38[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec39[0] > 0.0f)))));
			fRec38[0] = fVec36[((IOTA - 149) & 255)];
			int iTemp24 = (std::fabs((fTemp10 + -10.0f)) < 0.5f);
			iVec37[0] = iTemp24;
			fRec41[0] = ((fRec41[1] + float((float((iTemp24 - iVec37[1])) > 0.0f))) - (0.0199546479f * float((fRec41[1] > 0.0f))));
			fVec38[(IOTA & 63)] = ((fSlow18 * ((fTemp2 * fRec40[1]) + (fTemp3 * fRec40[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec41[0] > 0.0f)))));
			fRec40[0] = fVec38[((IOTA - 49) & 63)];
			int iTemp25 = (std::fabs((fTemp6 + -6.0f)) < 0.5f);
			iVec39[0] = iTemp25;
			fRec43[0] = ((fRec43[1] + float((float((iTemp25 - iVec39[1])) > 0.0f))) - (0.00593255227f * float((fRec43[1] > 0.0f))));
			fVec40[(IOTA & 255)] = ((fSlow19 * ((fTemp2 * fRec42[1]) + (fTemp3 * fRec42[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec43[0] > 0.0f)))));
			fRec42[0] = fVec40[((IOTA - 167) & 255)];
			int iTemp26 = (std::fabs((fTemp10 + -6.0f)) < 0.5f);
			iVec41[0] = iTemp26;
			fRec45[0] = ((fRec45[1] + float((float((iTemp26 - iVec41[1])) > 0.0f))) - (0.0118651045f * float((fRec45[1] > 0.0f))));
			fVec42[(IOTA & 127)] = ((fSlow20 * ((fTemp2 * fRec44[1]) + (fTemp3 * fRec44[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec45[0] > 0.0f)))));
			fRec44[0] = fVec42[((IOTA - 83) & 127)];
			int iTemp27 = (std::fabs((fTemp6 + -1.0f)) < 0.5f);
			iVec43[0] = iTemp27;
			fRec47[0] = ((fRec47[1] + float((float((iTemp27 - iVec43[1])) > 0.0f))) - (0.00296627614f * float((fRec47[1] > 0.0f))));
			fVec44[(IOTA & 511)] = ((fSlow21 * ((fRec46[1] * fTemp2) + (fTemp3 * fRec46[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec47[0] > 0.0f)))));
			fRec46[0] = fVec44[((IOTA - 336) & 511)];
			int iTemp28 = (std::fabs((fTemp6 + -11.0f)) < 0.5f);
			iVec45[0] = iTemp28;
			fRec49[0] = ((fRec49[1] + float((float((iTemp28 - iVec45[1])) > 0.0f))) - (0.0118651045f * float((fRec49[1] > 0.0f))));
			fVec46[(IOTA & 127)] = ((fSlow20 * ((fTemp2 * fRec48[1]) + (fTemp3 * fRec48[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec49[0] > 0.0f)))));
			fRec48[0] = fVec46[((IOTA - 83) & 127)];
			int iTemp29 = (std::fabs((fTemp10 + -1.0f)) < 0.5f);
			iVec47[0] = iTemp29;
			fRec51[0] = ((fRec51[1] + float((float((iTemp29 - iVec47[1])) > 0.0f))) - (0.00593255227f * float((fRec51[1] > 0.0f))));
			fVec48[(IOTA & 255)] = ((fSlow19 * ((fTemp2 * fRec50[1]) + (fTemp3 * fRec50[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec51[0] > 0.0f)))));
			fRec50[0] = fVec48[((IOTA - 167) & 255)];
			int iTemp30 = (std::fabs((fTemp10 + -11.0f)) < 0.5f);
			iVec49[0] = iTemp30;
			fRec53[0] = ((fRec53[1] + float((float((iTemp30 - iVec49[1])) > 0.0f))) - (0.0237302091f * float((fRec53[1] > 0.0f))));
			fVec50[(IOTA & 63)] = ((fSlow22 * ((fTemp2 * fRec52[1]) + (fTemp3 * fRec52[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec53[0] > 0.0f)))));
			fRec52[0] = fVec50[((IOTA - 41) & 63)];
			iVec51[0] = iSlow23;
			iRec56[0] = ((iVec1[1] + iRec56[1]) % iConst4);
			int iTemp31 = (iRec56[0] == 0);
			iVec52[0] = iTemp31;
			iRec57[0] = (iVec52[1] ? 0 : (iRec57[1] + std::abs((iSlow23 - iVec51[1]))));
			iRec58[0] = ((iTemp31 + iRec58[1]) % 15);
			ftbl3[((iTemp31 & ((iRec57[0] > 0) | iSlow24)) ? iRec58[0] : 15)] = float(iSlow23);
			float fTemp32 = ftbl3[iRec58[0]];
			int iTemp33 = (std::fabs((fTemp32 + -1.0f)) < 0.5f);
			iVec53[0] = iTemp33;
			fRec55[0] = ((fRec55[1] + float((float((iTemp33 - iVec53[1])) > 0.0f))) - (0.0118651045f * float((fRec55[1] > 0.0f))));
			fVec54[(IOTA & 127)] = ((fSlow20 * ((fTemp2 * fRec54[1]) + (fTemp3 * fRec54[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec55[0] > 0.0f)))));
			fRec54[0] = fVec54[((IOTA - 83) & 127)];
			int iTemp34 = (std::fabs((fTemp32 + -2.0f)) < 0.5f);
			iVec55[0] = iTemp34;
			fRec60[0] = ((fRec60[1] + float((float((iTemp34 - iVec55[1])) > 0.0f))) - (0.0133181298f * float((fRec60[1] > 0.0f))));
			fVec56[(IOTA & 127)] = ((fSlow10 * ((fTemp2 * fRec59[1]) + (fTemp3 * fRec59[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec60[0] > 0.0f)))));
			fRec59[0] = fVec56[((IOTA - 74) & 127)];
			int iTemp35 = (std::fabs((fTemp32 + -3.0f)) < 0.5f);
			iVec57[0] = iTemp35;
			fRec62[0] = ((fRec62[1] + float((float((iTemp35 - iVec57[1])) > 0.0f))) - (0.0149490954f * float((fRec62[1] > 0.0f))));
			fVec58[(IOTA & 127)] = ((fSlow14 * ((fTemp2 * fRec61[1]) + (fTemp3 * fRec61[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec62[0] > 0.0f)))));
			fRec61[0] = fVec58[((IOTA - 65) & 127)];
			int iTemp36 = (std::fabs((fTemp32 + -4.0f)) < 0.5f);
			iVec59[0] = iTemp36;
			fRec64[0] = ((fRec64[1] + float((float((iTemp36 - iVec59[1])) > 0.0f))) - (0.0177775715f * float((fRec64[1] > 0.0f))));
			fVec60[(IOTA & 63)] = ((fSlow16 * ((fTemp2 * fRec63[1]) + (fTemp3 * fRec63[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec64[0] > 0.0f)))));
			fRec63[0] = fVec60[((IOTA - 55) & 63)];
			int iTemp37 = (std::fabs((fTemp32 + -5.0f)) < 0.5f);
			iVec61[0] = iTemp37;
			fRec66[0] = ((fRec66[1] + float((float((iTemp37 - iVec61[1])) > 0.0f))) - (0.0199546479f * float((fRec66[1] > 0.0f))));
			fVec62[(IOTA & 63)] = ((fSlow18 * ((fTemp2 * fRec65[1]) + (fTemp3 * fRec65[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec66[0] > 0.0f)))));
			fRec65[0] = fVec62[((IOTA - 49) & 63)];
			int iTemp38 = (std::fabs((fTemp32 + -6.0f)) < 0.5f);
			iVec63[0] = iTemp38;
			fRec68[0] = ((fRec68[1] + float((float((iTemp38 - iVec63[1])) > 0.0f))) - (0.0237302091f * float((fRec68[1] > 0.0f))));
			fVec64[(IOTA & 63)] = ((fSlow22 * ((fTemp2 * fRec67[1]) + (fTemp3 * fRec67[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec68[0] > 0.0f)))));
			fRec67[0] = fVec64[((IOTA - 41) & 63)];
			float fTemp39 = (0.707106769f * fRec67[0]);
			int iTemp40 = (std::fabs((fTemp32 + -7.0f)) < 0.5f);
			iVec65[0] = iTemp40;
			fRec70[0] = ((fRec70[1] + float((float((iTemp40 - iVec65[1])) > 0.0f))) - (0.0266362596f * float((fRec70[1] > 0.0f))));
			fVec66[(IOTA & 63)] = ((fSlow25 * ((fTemp2 * fRec69[1]) + (fTemp3 * fRec69[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec70[0] > 0.0f)))));
			fRec69[0] = fVec66[((IOTA - 36) & 63)];
			int iTemp41 = (std::fabs((fTemp32 + -8.0f)) < 0.5f);
			iVec67[0] = iTemp41;
			fRec72[0] = ((fRec72[1] + float((float((iTemp41 - iVec67[1])) > 0.0f))) - (0.0298981909f * float((fRec72[1] > 0.0f))));
			fVec68[(IOTA & 63)] = ((fSlow26 * ((fTemp2 * fRec71[1]) + (fTemp3 * fRec71[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec72[0] > 0.0f)))));
			fRec71[0] = fVec68[((IOTA - 32) & 63)];
			int iTemp42 = (std::fabs((fTemp32 + -9.0f)) < 0.5f);
			iVec69[0] = iTemp42;
			fRec74[0] = ((fRec74[1] + float((float((iTemp42 - iVec69[1])) > 0.0f))) - (0.0355551429f * float((fRec74[1] > 0.0f))));
			fVec70[(IOTA & 31)] = ((fSlow27 * ((fTemp2 * fRec73[1]) + (fTemp3 * fRec73[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec74[0] > 0.0f)))));
			fRec73[0] = fVec70[((IOTA - 27) & 31)];
			int iTemp43 = (std::fabs((fTemp32 + -10.0f)) < 0.5f);
			iVec71[0] = iTemp43;
			fRec76[0] = ((fRec76[1] + float((float((iTemp43 - iVec71[1])) > 0.0f))) - (0.0399092957f * float((fRec76[1] > 0.0f))));
			fVec72[(IOTA & 31)] = ((fSlow28 * ((fTemp2 * fRec75[1]) + (fTemp3 * fRec75[2]))) + (4.65661287e-10f * (fTemp4 * float((fRec76[0] > 0.0f)))));
			fRec75[0] = fVec72[((IOTA - 24) & 31)];
			int iTemp44 = (std::fabs((fTemp32 + -11.0f)) < 0.5f);
			iVec73[0] = iTemp44;
			fRec78[0] = ((fRec78[1] + float((float((iTemp44 - iVec73[1])) > 0.0f))) - (0.0474604182f * float((fRec78[1] > 0.0f))));
			fVec74[(IOTA & 31)] = ((fSlow29 * ((fTemp2 * fRec77[1]) + (fTemp3 * fRec77[2]))) + (4.65661287e-10f * (float((fRec78[0] > 0.0f)) * fTemp4)));
			fRec77[0] = fVec74[((IOTA - 20) & 31)];
			output0[i] = FAUSTFLOAT((0.100000001f * (((1.40830827f * ((fRec0[0] + fRec9[0]) + (fRec11[0] + fRec16[0]))) + ((1.38979888f * ((fRec18[0] + fRec20[0]) + (fRec22[0] + fRec24[0]))) + ((1.35578036f * ((fRec26[0] + fRec28[0]) + (fRec30[0] + fRec32[0]))) + ((1.29859483f * ((fRec34[0] + fRec36[0]) + (fRec38[0] + fRec40[0]))) + ((1.41421354f * (fRec42[0] + fRec44[0])) + (1.19020915f * ((fRec46[0] + fRec48[0]) + (fRec50[0] + fRec52[0])))))))) + (1.5f * ((((((((((((0.977008402f * fRec54[0]) + (0.929320395f * fRec59[0])) + (0.879049063f * fRec61[0])) + (0.825722814f * fRec63[0])) + (0.768706143f * fRec65[0])) + fTemp39) + (0.639602125f * fRec69[0])) + (0.564076066f * fRec71[0])) + (0.4767313f * fRec73[0])) + (0.369274467f * fRec75[0])) + (0.213200718f * fRec77[0])) + ((((((fTemp39 + (((((0.213200718f * fRec54[0]) + (0.369274467f * fRec59[0])) + (0.4767313f * fRec61[0])) + (0.564076066f * fRec63[0])) + (0.639602125f * fRec65[0]))) + (0.768706143f * fRec69[0])) + (0.825722814f * fRec71[0])) + (0.879049063f * fRec73[0])) + (0.929320395f * fRec75[0])) + (0.977008402f * fRec77[0])))))));
			fVec0[1] = fVec0[0];
			iVec1[1] = iVec1[0];
			iRec1[1] = iRec1[0];
			iVec2[1] = iVec2[0];
			fRec2[1] = fRec2[0];
			iRec3[1] = iRec3[0];
			iRec4[1] = iRec4[0];
			iVec3[1] = iVec3[0];
			iRec6[1] = iRec6[0];
			iVec4[1] = iVec4[0];
			iRec7[1] = iRec7[0];
			iRec8[1] = iRec8[0];
			iVec5[1] = iVec5[0];
			fRec5[1] = fRec5[0];
			IOTA = (IOTA + 1);
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			iVec7[1] = iVec7[0];
			fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			iVec9[1] = iVec9[0];
			iRec13[1] = iRec13[0];
			iVec10[1] = iVec10[0];
			iRec14[1] = iRec14[0];
			iRec15[1] = iRec15[0];
			iVec11[1] = iVec11[0];
			fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			iVec13[1] = iVec13[0];
			fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			iVec15[1] = iVec15[0];
			fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			iVec17[1] = iVec17[0];
			fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			iVec19[1] = iVec19[0];
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			iVec21[1] = iVec21[0];
			fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			iVec23[1] = iVec23[0];
			fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			iVec25[1] = iVec25[0];
			fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			iVec27[1] = iVec27[0];
			fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			iVec29[1] = iVec29[0];
			fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			iVec31[1] = iVec31[0];
			fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			iVec33[1] = iVec33[0];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			iVec35[1] = iVec35[0];
			fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			iVec37[1] = iVec37[0];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			iVec39[1] = iVec39[0];
			fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			iVec41[1] = iVec41[0];
			fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			iVec43[1] = iVec43[0];
			fRec47[1] = fRec47[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			iVec45[1] = iVec45[0];
			fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			iVec47[1] = iVec47[0];
			fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			iVec49[1] = iVec49[0];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			iVec51[1] = iVec51[0];
			iRec56[1] = iRec56[0];
			iVec52[1] = iVec52[0];
			iRec57[1] = iRec57[0];
			iRec58[1] = iRec58[0];
			iVec53[1] = iVec53[0];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			iVec55[1] = iVec55[0];
			fRec60[1] = fRec60[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			iVec57[1] = iVec57[0];
			fRec62[1] = fRec62[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			iVec59[1] = iVec59[0];
			fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			iVec61[1] = iVec61[0];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			iVec63[1] = iVec63[0];
			fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			iVec65[1] = iVec65[0];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			iVec67[1] = iVec67[0];
			fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			iVec69[1] = iVec69[0];
			fRec74[1] = fRec74[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			iVec71[1] = iVec71[0];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			iVec73[1] = iVec73[0];
			fRec78[1] = fRec78[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
		}
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

//#define A1S_BOARD true                  //uncomment for Ai-thinker A1S board

#define MULT_S32 2147483647
#define DIV_S32 4.6566129e-10
#define clip(sample) std::max(-MULT_S32, std::min(MULT_S32, ((int32_t)(sample * MULT_S32))));

karplus::karplus(int sample_rate, int buffer_size)
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

karplus::~karplus()
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

bool karplus::start()
{
    xTaskCreate(audioTaskHandler, "Faust DSP Task", 1024, (void*)this, 5, &fHandle);
    return true;
}

void karplus::stop()
{
    if (fHandle != NULL) {
        vTaskDelete(fHandle);
        fHandle = NULL;
    }
}

void karplus::setParamValue(const std::string& path, float value)
{
    fUI->setParamValue(path, value);
}

void karplus::configureI2S(int sample_rate, int buffer_size, i2s_pin_config_t pin_config)
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

void karplus::audioTask()
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

void karplus::audioTaskHandler(void* arg)
{
    karplus* audio = (karplus*)arg;
    audio->audioTask();
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

#endif

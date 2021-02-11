/* ------------------------------------------------------------
name: "virtualAnalogLab"
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

#include "lab.h"

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
	
	FAUSTFLOAT fHslider0;
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider1;
	int iVec0[4];
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fHslider2;
	float fRec4[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fEntry0;
	float fConst14;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fVslider2;
	float fRec6[2];
	float fVec1[2];
	float fRec5[2];
	float fConst15;
	float fVec2[2];
	float fConst16;
	float fVec3[2];
	float fVec4[2];
	float fConst17;
	float fVec5[2];
	float fVec6[2];
	float fVec7[2];
	FAUSTFLOAT fVslider3;
	float fVec8[2];
	float fRec7[2];
	float fVec9[2];
	float fVec10[2];
	float fVec11[2];
	float fVec12[2];
	float fVec13[2];
	float fVec14[2];
	FAUSTFLOAT fVslider4;
	float fVec15[2];
	float fRec8[2];
	float fVec16[2];
	float fVec17[2];
	float fVec18[2];
	float fVec19[2];
	float fVec20[2];
	float fVec21[2];
	float fConst18;
	FAUSTFLOAT fVslider5;
	float fVec22[2];
	float fRec9[2];
	float fVec23[2];
	int IOTA;
	float fVec24[4096];
	float fConst19;
	float fVec25[2];
	float fRec10[2];
	float fVec26[2];
	float fVec27[4096];
	float fVec28[2];
	float fRec11[2];
	float fVec29[2];
	float fVec30[4096];
	float fConst20;
	FAUSTFLOAT fVslider6;
	float fRec12[2];
	float fRec13[2];
	float fRec14[2];
	FAUSTFLOAT fVslider7;
	float fConst21;
	FAUSTFLOAT fCheckbox0;
	float fVec31[2];
	float fVec32[2];
	float fVec33[4096];
	FAUSTFLOAT fVslider8;
	float fRec15[2];
	float fVec34[2];
	float fVec35[2];
	float fVec36[4096];
	float fVec37[2];
	float fVec38[2];
	float fVec39[4096];
	FAUSTFLOAT fVslider9;
	int iRec17[2];
	float fRec16[4];
	float fConst22;
	float fConst23;
	float fConst24;
	float fRec3[3];
	float fConst25;
	float fConst26;
	float fConst27;
	float fRec2[3];
	float fConst28;
	float fConst29;
	float fConst30;
	float fRec1[3];
	float fConst31;
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	float fConst32;
	float fConst33;
	float fConst34;
	float fConst35;
	float fConst36;
	float fConst37;
	float fConst38;
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fConst44;
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fConst51;
	float fConst52;
	float fRec24[3];
	float fConst53;
	float fConst54;
	float fConst55;
	float fRec23[3];
	float fConst56;
	float fConst57;
	float fConst58;
	float fRec22[3];
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec21[3];
	float fConst63;
	float fConst64;
	float fConst65;
	float fRec20[3];
	float fConst66;
	float fConst67;
	float fConst68;
	float fRec19[3];
	float fConst69;
	float fRec18[2];
	FAUSTFLOAT fVbargraph1;
	float fConst70;
	float fConst71;
	float fConst72;
	float fConst73;
	float fConst74;
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fConst80;
	float fConst81;
	float fConst82;
	float fConst83;
	float fConst84;
	float fConst85;
	float fConst86;
	float fConst87;
	float fConst88;
	float fConst89;
	float fConst90;
	float fRec31[3];
	float fConst91;
	float fConst92;
	float fConst93;
	float fRec30[3];
	float fConst94;
	float fConst95;
	float fConst96;
	float fRec29[3];
	float fConst97;
	float fConst98;
	float fConst99;
	float fConst100;
	float fRec28[3];
	float fConst101;
	float fConst102;
	float fConst103;
	float fRec27[3];
	float fConst104;
	float fConst105;
	float fConst106;
	float fRec26[3];
	float fConst107;
	float fRec25[2];
	FAUSTFLOAT fVbargraph2;
	float fConst108;
	float fConst109;
	float fConst110;
	float fConst111;
	float fConst112;
	float fConst113;
	float fConst114;
	float fConst115;
	float fConst116;
	float fConst117;
	float fConst118;
	float fConst119;
	float fConst120;
	float fConst121;
	float fConst122;
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fConst127;
	float fConst128;
	float fRec38[3];
	float fConst129;
	float fConst130;
	float fConst131;
	float fRec37[3];
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec36[3];
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fRec35[3];
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec34[3];
	float fConst142;
	float fConst143;
	float fConst144;
	float fRec33[3];
	float fConst145;
	float fRec32[2];
	FAUSTFLOAT fVbargraph3;
	float fConst146;
	float fConst147;
	float fConst148;
	float fConst149;
	float fConst150;
	float fConst151;
	float fConst152;
	float fConst153;
	float fConst154;
	float fConst155;
	float fConst156;
	float fConst157;
	float fConst158;
	float fConst159;
	float fConst160;
	float fConst161;
	float fConst162;
	float fConst163;
	float fConst164;
	float fConst165;
	float fConst166;
	float fRec45[3];
	float fConst167;
	float fConst168;
	float fConst169;
	float fRec44[3];
	float fConst170;
	float fConst171;
	float fConst172;
	float fRec43[3];
	float fConst173;
	float fConst174;
	float fConst175;
	float fConst176;
	float fRec42[3];
	float fConst177;
	float fConst178;
	float fConst179;
	float fRec41[3];
	float fConst180;
	float fConst181;
	float fConst182;
	float fRec40[3];
	float fConst183;
	float fRec39[2];
	FAUSTFLOAT fVbargraph4;
	float fConst184;
	float fConst185;
	float fConst186;
	float fConst187;
	float fConst188;
	float fConst189;
	float fConst190;
	float fConst191;
	float fConst192;
	float fConst193;
	float fConst194;
	float fConst195;
	float fConst196;
	float fConst197;
	float fConst198;
	float fConst199;
	float fConst200;
	float fConst201;
	float fConst202;
	float fConst203;
	float fConst204;
	float fRec52[3];
	float fConst205;
	float fConst206;
	float fConst207;
	float fRec51[3];
	float fConst208;
	float fConst209;
	float fConst210;
	float fRec50[3];
	float fConst211;
	float fConst212;
	float fConst213;
	float fConst214;
	float fRec49[3];
	float fConst215;
	float fConst216;
	float fConst217;
	float fRec48[3];
	float fConst218;
	float fConst219;
	float fConst220;
	float fRec47[3];
	float fConst221;
	float fRec46[2];
	FAUSTFLOAT fVbargraph5;
	float fConst222;
	float fConst223;
	float fConst224;
	float fConst225;
	float fConst226;
	float fConst227;
	float fConst228;
	float fConst229;
	float fConst230;
	float fConst231;
	float fConst232;
	float fConst233;
	float fConst234;
	float fConst235;
	float fConst236;
	float fConst237;
	float fConst238;
	float fConst239;
	float fConst240;
	float fConst241;
	float fConst242;
	float fRec59[3];
	float fConst243;
	float fConst244;
	float fConst245;
	float fRec58[3];
	float fConst246;
	float fConst247;
	float fConst248;
	float fRec57[3];
	float fConst249;
	float fConst250;
	float fConst251;
	float fConst252;
	float fRec56[3];
	float fConst253;
	float fConst254;
	float fConst255;
	float fRec55[3];
	float fConst256;
	float fConst257;
	float fConst258;
	float fRec54[3];
	float fConst259;
	float fRec53[2];
	FAUSTFLOAT fVbargraph6;
	float fConst260;
	float fConst261;
	float fConst262;
	float fConst263;
	float fConst264;
	float fConst265;
	float fConst266;
	float fConst267;
	float fConst268;
	float fConst269;
	float fConst270;
	float fConst271;
	float fConst272;
	float fConst273;
	float fConst274;
	float fConst275;
	float fConst276;
	float fConst277;
	float fConst278;
	float fConst279;
	float fConst280;
	float fRec66[3];
	float fConst281;
	float fConst282;
	float fConst283;
	float fRec65[3];
	float fConst284;
	float fConst285;
	float fConst286;
	float fRec64[3];
	float fConst287;
	float fConst288;
	float fConst289;
	float fConst290;
	float fRec63[3];
	float fConst291;
	float fConst292;
	float fConst293;
	float fRec62[3];
	float fConst294;
	float fConst295;
	float fConst296;
	float fRec61[3];
	float fConst297;
	float fRec60[2];
	FAUSTFLOAT fVbargraph7;
	float fConst298;
	float fConst299;
	float fConst300;
	float fConst301;
	float fConst302;
	float fConst303;
	float fConst304;
	float fConst305;
	float fConst306;
	float fConst307;
	float fConst308;
	float fConst309;
	float fConst310;
	float fConst311;
	float fConst312;
	float fConst313;
	float fConst314;
	float fConst315;
	float fConst316;
	float fConst317;
	float fConst318;
	float fRec73[3];
	float fConst319;
	float fConst320;
	float fConst321;
	float fRec72[3];
	float fConst322;
	float fConst323;
	float fConst324;
	float fRec71[3];
	float fConst325;
	float fConst326;
	float fConst327;
	float fConst328;
	float fRec70[3];
	float fConst329;
	float fConst330;
	float fConst331;
	float fRec69[3];
	float fConst332;
	float fConst333;
	float fConst334;
	float fRec68[3];
	float fConst335;
	float fRec67[2];
	FAUSTFLOAT fVbargraph8;
	float fConst336;
	float fConst337;
	float fConst338;
	float fConst339;
	float fConst340;
	float fConst341;
	float fConst342;
	float fConst343;
	float fConst344;
	float fConst345;
	float fConst346;
	float fConst347;
	float fConst348;
	float fConst349;
	float fConst350;
	float fConst351;
	float fConst352;
	float fConst353;
	float fConst354;
	float fConst355;
	float fConst356;
	float fRec80[3];
	float fConst357;
	float fConst358;
	float fConst359;
	float fRec79[3];
	float fConst360;
	float fConst361;
	float fConst362;
	float fRec78[3];
	float fConst363;
	float fConst364;
	float fConst365;
	float fConst366;
	float fRec77[3];
	float fConst367;
	float fConst368;
	float fConst369;
	float fRec76[3];
	float fConst370;
	float fConst371;
	float fConst372;
	float fRec75[3];
	float fConst373;
	float fRec74[2];
	FAUSTFLOAT fVbargraph9;
	float fConst374;
	float fConst375;
	float fConst376;
	float fConst377;
	float fConst378;
	float fConst379;
	float fConst380;
	float fConst381;
	float fConst382;
	float fConst383;
	float fConst384;
	float fConst385;
	float fConst386;
	float fConst387;
	float fConst388;
	float fConst389;
	float fConst390;
	float fConst391;
	float fConst392;
	float fConst393;
	float fConst394;
	float fRec87[3];
	float fConst395;
	float fConst396;
	float fConst397;
	float fRec86[3];
	float fConst398;
	float fConst399;
	float fConst400;
	float fRec85[3];
	float fConst401;
	float fConst402;
	float fConst403;
	float fConst404;
	float fRec84[3];
	float fConst405;
	float fConst406;
	float fConst407;
	float fRec83[3];
	float fConst408;
	float fConst409;
	float fConst410;
	float fRec82[3];
	float fConst411;
	float fRec81[2];
	FAUSTFLOAT fVbargraph10;
	float fConst412;
	float fConst413;
	float fConst414;
	float fConst415;
	float fConst416;
	float fConst417;
	float fConst418;
	float fConst419;
	float fConst420;
	float fConst421;
	float fConst422;
	float fConst423;
	float fConst424;
	float fConst425;
	float fConst426;
	float fConst427;
	float fConst428;
	float fConst429;
	float fConst430;
	float fConst431;
	float fConst432;
	float fRec94[3];
	float fConst433;
	float fConst434;
	float fConst435;
	float fRec93[3];
	float fConst436;
	float fConst437;
	float fConst438;
	float fRec92[3];
	float fConst439;
	float fConst440;
	float fConst441;
	float fConst442;
	float fRec91[3];
	float fConst443;
	float fConst444;
	float fConst445;
	float fRec90[3];
	float fConst446;
	float fConst447;
	float fConst448;
	float fRec89[3];
	float fConst449;
	float fRec88[2];
	FAUSTFLOAT fVbargraph11;
	float fConst450;
	float fConst451;
	float fConst452;
	float fConst453;
	float fConst454;
	float fConst455;
	float fConst456;
	float fConst457;
	float fConst458;
	float fConst459;
	float fConst460;
	float fConst461;
	float fConst462;
	float fConst463;
	float fConst464;
	float fConst465;
	float fConst466;
	float fConst467;
	float fConst468;
	float fConst469;
	float fConst470;
	float fRec101[3];
	float fConst471;
	float fConst472;
	float fConst473;
	float fRec100[3];
	float fConst474;
	float fConst475;
	float fConst476;
	float fRec99[3];
	float fConst477;
	float fConst478;
	float fConst479;
	float fConst480;
	float fRec98[3];
	float fConst481;
	float fConst482;
	float fConst483;
	float fRec97[3];
	float fConst484;
	float fConst485;
	float fConst486;
	float fRec96[3];
	float fConst487;
	float fRec95[2];
	FAUSTFLOAT fVbargraph12;
	float fConst488;
	float fConst489;
	float fConst490;
	float fConst491;
	float fConst492;
	float fConst493;
	float fConst494;
	float fConst495;
	float fConst496;
	float fConst497;
	float fConst498;
	float fConst499;
	float fConst500;
	float fConst501;
	float fConst502;
	float fConst503;
	float fConst504;
	float fConst505;
	float fConst506;
	float fConst507;
	float fConst508;
	float fRec108[3];
	float fConst509;
	float fConst510;
	float fConst511;
	float fRec107[3];
	float fConst512;
	float fConst513;
	float fConst514;
	float fRec106[3];
	float fConst515;
	float fConst516;
	float fConst517;
	float fConst518;
	float fRec105[3];
	float fConst519;
	float fConst520;
	float fConst521;
	float fRec104[3];
	float fConst522;
	float fConst523;
	float fConst524;
	float fRec103[3];
	float fConst525;
	float fRec102[2];
	FAUSTFLOAT fVbargraph13;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fConst533;
	float fConst534;
	float fRec112[3];
	float fConst535;
	float fConst536;
	float fConst537;
	float fRec111[3];
	float fConst538;
	float fConst539;
	float fConst540;
	float fRec110[3];
	float fConst541;
	float fRec109[2];
	FAUSTFLOAT fVbargraph14;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("filename", "lab.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass6e:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass6e:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/highpass6e:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass6e:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass6e:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass6e:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "virtualAnalogLab");
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
		fConst1 = (1000.0f / fConst0);
		fConst2 = std::tan((50265.4844f / fConst0));
		fConst3 = (1.0f / fConst2);
		fConst4 = (1.0f / (((fConst3 + 0.157482162f) / fConst2) + 0.935140193f));
		fConst5 = mydsp_faustpower2_f(fConst2);
		fConst6 = (50.0638084f / fConst5);
		fConst7 = (fConst6 + 0.935140193f);
		fConst8 = (1.0f / (((fConst3 + 0.743130445f) / fConst2) + 1.4500711f));
		fConst9 = (11.0520525f / fConst5);
		fConst10 = (fConst9 + 1.4500711f);
		fConst11 = (1.0f / (((fConst3 + 3.18972731f) / fConst2) + 4.07678175f));
		fConst12 = (0.00176617282f / fConst5);
		fConst13 = (fConst12 + 0.000407678192f);
		fConst14 = (1.0f / fConst0);
		fConst15 = (0.25f * fConst0);
		fConst16 = (0.0416666679f * mydsp_faustpower2_f(fConst0));
		fConst17 = (0.00520833349f * mydsp_faustpower3_f(fConst0));
		fConst18 = (0.0833333358f * fConst0);
		fConst19 = (0.5f * fConst0);
		fConst20 = (1.33333337f / fConst0);
		fConst21 = (0.013888889f * fConst0);
		fConst22 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst23 = (1.0f / fConst5);
		fConst24 = (2.0f * (4.07678175f - fConst23));
		fConst25 = (2.0f * (0.000407678192f - fConst12));
		fConst26 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst27 = (2.0f * (1.4500711f - fConst23));
		fConst28 = (2.0f * (1.4500711f - fConst9));
		fConst29 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst30 = (2.0f * (0.935140193f - fConst23));
		fConst31 = (2.0f * (0.935140193f - fConst6));
		fConst32 = std::tan((31665.2695f / fConst0));
		fConst33 = (1.0f / fConst32);
		fConst34 = (1.0f / (((fConst33 + 0.157482162f) / fConst32) + 0.935140193f));
		fConst35 = mydsp_faustpower2_f(fConst32);
		fConst36 = (50.0638084f / fConst35);
		fConst37 = (fConst36 + 0.935140193f);
		fConst38 = (1.0f / (((fConst33 + 0.743130445f) / fConst32) + 1.4500711f));
		fConst39 = (11.0520525f / fConst35);
		fConst40 = (fConst39 + 1.4500711f);
		fConst41 = (1.0f / (((fConst33 + 3.18972731f) / fConst32) + 4.07678175f));
		fConst42 = (0.00176617282f / fConst35);
		fConst43 = (fConst42 + 0.000407678192f);
		fConst44 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst45 = (fConst23 + 53.5361519f);
		fConst46 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst47 = (fConst23 + 7.62173128f);
		fConst48 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst49 = (9.99999975e-05f / fConst5);
		fConst50 = (fConst49 + 0.000433227193f);
		fConst51 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst52 = (2.0f * (0.245291501f - fConst23));
		fConst53 = (2.0f * (0.000433227193f - fConst49));
		fConst54 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst55 = (2.0f * (0.689621389f - fConst23));
		fConst56 = (2.0f * (7.62173128f - fConst23));
		fConst57 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst58 = (2.0f * (1.06935835f - fConst23));
		fConst59 = (2.0f * (53.5361519f - fConst23));
		fConst60 = (((fConst33 + -3.18972731f) / fConst32) + 4.07678175f);
		fConst61 = (1.0f / fConst35);
		fConst62 = (2.0f * (4.07678175f - fConst61));
		fConst63 = (2.0f * (0.000407678192f - fConst42));
		fConst64 = (((fConst33 + -0.743130445f) / fConst32) + 1.4500711f);
		fConst65 = (2.0f * (1.4500711f - fConst61));
		fConst66 = (2.0f * (1.4500711f - fConst39));
		fConst67 = (((fConst33 + -0.157482162f) / fConst32) + 0.935140193f);
		fConst68 = (2.0f * (0.935140193f - fConst61));
		fConst69 = (2.0f * (0.935140193f - fConst36));
		fConst70 = std::tan((19947.8691f / fConst0));
		fConst71 = (1.0f / fConst70);
		fConst72 = (1.0f / (((fConst71 + 0.157482162f) / fConst70) + 0.935140193f));
		fConst73 = mydsp_faustpower2_f(fConst70);
		fConst74 = (50.0638084f / fConst73);
		fConst75 = (fConst74 + 0.935140193f);
		fConst76 = (1.0f / (((fConst71 + 0.743130445f) / fConst70) + 1.4500711f));
		fConst77 = (11.0520525f / fConst73);
		fConst78 = (fConst77 + 1.4500711f);
		fConst79 = (1.0f / (((fConst71 + 3.18972731f) / fConst70) + 4.07678175f));
		fConst80 = (0.00176617282f / fConst73);
		fConst81 = (fConst80 + 0.000407678192f);
		fConst82 = (1.0f / (((fConst33 + 0.168404877f) / fConst32) + 1.06935835f));
		fConst83 = (fConst61 + 53.5361519f);
		fConst84 = (1.0f / (((fConst33 + 0.51247865f) / fConst32) + 0.689621389f));
		fConst85 = (fConst61 + 7.62173128f);
		fConst86 = (1.0f / (((fConst33 + 0.782413065f) / fConst32) + 0.245291501f));
		fConst87 = (9.99999975e-05f / fConst35);
		fConst88 = (fConst87 + 0.000433227193f);
		fConst89 = (((fConst33 + -0.782413065f) / fConst32) + 0.245291501f);
		fConst90 = (2.0f * (0.245291501f - fConst61));
		fConst91 = (2.0f * (0.000433227193f - fConst87));
		fConst92 = (((fConst33 + -0.51247865f) / fConst32) + 0.689621389f);
		fConst93 = (2.0f * (0.689621389f - fConst61));
		fConst94 = (2.0f * (7.62173128f - fConst61));
		fConst95 = (((fConst33 + -0.168404877f) / fConst32) + 1.06935835f);
		fConst96 = (2.0f * (1.06935835f - fConst61));
		fConst97 = (2.0f * (53.5361519f - fConst61));
		fConst98 = (((fConst71 + -3.18972731f) / fConst70) + 4.07678175f);
		fConst99 = (1.0f / fConst73);
		fConst100 = (2.0f * (4.07678175f - fConst99));
		fConst101 = (2.0f * (0.000407678192f - fConst80));
		fConst102 = (((fConst71 + -0.743130445f) / fConst70) + 1.4500711f);
		fConst103 = (2.0f * (1.4500711f - fConst99));
		fConst104 = (2.0f * (1.4500711f - fConst77));
		fConst105 = (((fConst71 + -0.157482162f) / fConst70) + 0.935140193f);
		fConst106 = (2.0f * (0.935140193f - fConst99));
		fConst107 = (2.0f * (0.935140193f - fConst74));
		fConst108 = std::tan((12566.3711f / fConst0));
		fConst109 = (1.0f / fConst108);
		fConst110 = (1.0f / (((fConst109 + 0.157482162f) / fConst108) + 0.935140193f));
		fConst111 = mydsp_faustpower2_f(fConst108);
		fConst112 = (50.0638084f / fConst111);
		fConst113 = (fConst112 + 0.935140193f);
		fConst114 = (1.0f / (((fConst109 + 0.743130445f) / fConst108) + 1.4500711f));
		fConst115 = (11.0520525f / fConst111);
		fConst116 = (fConst115 + 1.4500711f);
		fConst117 = (1.0f / (((fConst109 + 3.18972731f) / fConst108) + 4.07678175f));
		fConst118 = (0.00176617282f / fConst111);
		fConst119 = (fConst118 + 0.000407678192f);
		fConst120 = (1.0f / (((fConst71 + 0.168404877f) / fConst70) + 1.06935835f));
		fConst121 = (fConst99 + 53.5361519f);
		fConst122 = (1.0f / (((fConst71 + 0.51247865f) / fConst70) + 0.689621389f));
		fConst123 = (fConst99 + 7.62173128f);
		fConst124 = (1.0f / (((fConst71 + 0.782413065f) / fConst70) + 0.245291501f));
		fConst125 = (9.99999975e-05f / fConst73);
		fConst126 = (fConst125 + 0.000433227193f);
		fConst127 = (((fConst71 + -0.782413065f) / fConst70) + 0.245291501f);
		fConst128 = (2.0f * (0.245291501f - fConst99));
		fConst129 = (2.0f * (0.000433227193f - fConst125));
		fConst130 = (((fConst71 + -0.51247865f) / fConst70) + 0.689621389f);
		fConst131 = (2.0f * (0.689621389f - fConst99));
		fConst132 = (2.0f * (7.62173128f - fConst99));
		fConst133 = (((fConst71 + -0.168404877f) / fConst70) + 1.06935835f);
		fConst134 = (2.0f * (1.06935835f - fConst99));
		fConst135 = (2.0f * (53.5361519f - fConst99));
		fConst136 = (((fConst109 + -3.18972731f) / fConst108) + 4.07678175f);
		fConst137 = (1.0f / fConst111);
		fConst138 = (2.0f * (4.07678175f - fConst137));
		fConst139 = (2.0f * (0.000407678192f - fConst118));
		fConst140 = (((fConst109 + -0.743130445f) / fConst108) + 1.4500711f);
		fConst141 = (2.0f * (1.4500711f - fConst137));
		fConst142 = (2.0f * (1.4500711f - fConst115));
		fConst143 = (((fConst109 + -0.157482162f) / fConst108) + 0.935140193f);
		fConst144 = (2.0f * (0.935140193f - fConst137));
		fConst145 = (2.0f * (0.935140193f - fConst112));
		fConst146 = std::tan((7916.31738f / fConst0));
		fConst147 = (1.0f / fConst146);
		fConst148 = (1.0f / (((fConst147 + 0.157482162f) / fConst146) + 0.935140193f));
		fConst149 = mydsp_faustpower2_f(fConst146);
		fConst150 = (50.0638084f / fConst149);
		fConst151 = (fConst150 + 0.935140193f);
		fConst152 = (1.0f / (((fConst147 + 0.743130445f) / fConst146) + 1.4500711f));
		fConst153 = (11.0520525f / fConst149);
		fConst154 = (fConst153 + 1.4500711f);
		fConst155 = (1.0f / (((fConst147 + 3.18972731f) / fConst146) + 4.07678175f));
		fConst156 = (0.00176617282f / fConst149);
		fConst157 = (fConst156 + 0.000407678192f);
		fConst158 = (1.0f / (((fConst109 + 0.168404877f) / fConst108) + 1.06935835f));
		fConst159 = (fConst137 + 53.5361519f);
		fConst160 = (1.0f / (((fConst109 + 0.51247865f) / fConst108) + 0.689621389f));
		fConst161 = (fConst137 + 7.62173128f);
		fConst162 = (1.0f / (((fConst109 + 0.782413065f) / fConst108) + 0.245291501f));
		fConst163 = (9.99999975e-05f / fConst111);
		fConst164 = (fConst163 + 0.000433227193f);
		fConst165 = (((fConst109 + -0.782413065f) / fConst108) + 0.245291501f);
		fConst166 = (2.0f * (0.245291501f - fConst137));
		fConst167 = (2.0f * (0.000433227193f - fConst163));
		fConst168 = (((fConst109 + -0.51247865f) / fConst108) + 0.689621389f);
		fConst169 = (2.0f * (0.689621389f - fConst137));
		fConst170 = (2.0f * (7.62173128f - fConst137));
		fConst171 = (((fConst109 + -0.168404877f) / fConst108) + 1.06935835f);
		fConst172 = (2.0f * (1.06935835f - fConst137));
		fConst173 = (2.0f * (53.5361519f - fConst137));
		fConst174 = (((fConst147 + -3.18972731f) / fConst146) + 4.07678175f);
		fConst175 = (1.0f / fConst149);
		fConst176 = (2.0f * (4.07678175f - fConst175));
		fConst177 = (2.0f * (0.000407678192f - fConst156));
		fConst178 = (((fConst147 + -0.743130445f) / fConst146) + 1.4500711f);
		fConst179 = (2.0f * (1.4500711f - fConst175));
		fConst180 = (2.0f * (1.4500711f - fConst153));
		fConst181 = (((fConst147 + -0.157482162f) / fConst146) + 0.935140193f);
		fConst182 = (2.0f * (0.935140193f - fConst175));
		fConst183 = (2.0f * (0.935140193f - fConst150));
		fConst184 = std::tan((4986.96729f / fConst0));
		fConst185 = (1.0f / fConst184);
		fConst186 = (1.0f / (((fConst185 + 0.157482162f) / fConst184) + 0.935140193f));
		fConst187 = mydsp_faustpower2_f(fConst184);
		fConst188 = (50.0638084f / fConst187);
		fConst189 = (fConst188 + 0.935140193f);
		fConst190 = (1.0f / (((fConst185 + 0.743130445f) / fConst184) + 1.4500711f));
		fConst191 = (11.0520525f / fConst187);
		fConst192 = (fConst191 + 1.4500711f);
		fConst193 = (1.0f / (((fConst185 + 3.18972731f) / fConst184) + 4.07678175f));
		fConst194 = (0.00176617282f / fConst187);
		fConst195 = (fConst194 + 0.000407678192f);
		fConst196 = (1.0f / (((fConst147 + 0.168404877f) / fConst146) + 1.06935835f));
		fConst197 = (fConst175 + 53.5361519f);
		fConst198 = (1.0f / (((fConst147 + 0.51247865f) / fConst146) + 0.689621389f));
		fConst199 = (fConst175 + 7.62173128f);
		fConst200 = (1.0f / (((fConst147 + 0.782413065f) / fConst146) + 0.245291501f));
		fConst201 = (9.99999975e-05f / fConst149);
		fConst202 = (fConst201 + 0.000433227193f);
		fConst203 = (((fConst147 + -0.782413065f) / fConst146) + 0.245291501f);
		fConst204 = (2.0f * (0.245291501f - fConst175));
		fConst205 = (2.0f * (0.000433227193f - fConst201));
		fConst206 = (((fConst147 + -0.51247865f) / fConst146) + 0.689621389f);
		fConst207 = (2.0f * (0.689621389f - fConst175));
		fConst208 = (2.0f * (7.62173128f - fConst175));
		fConst209 = (((fConst147 + -0.168404877f) / fConst146) + 1.06935835f);
		fConst210 = (2.0f * (1.06935835f - fConst175));
		fConst211 = (2.0f * (53.5361519f - fConst175));
		fConst212 = (((fConst185 + -3.18972731f) / fConst184) + 4.07678175f);
		fConst213 = (1.0f / fConst187);
		fConst214 = (2.0f * (4.07678175f - fConst213));
		fConst215 = (2.0f * (0.000407678192f - fConst194));
		fConst216 = (((fConst185 + -0.743130445f) / fConst184) + 1.4500711f);
		fConst217 = (2.0f * (1.4500711f - fConst213));
		fConst218 = (2.0f * (1.4500711f - fConst191));
		fConst219 = (((fConst185 + -0.157482162f) / fConst184) + 0.935140193f);
		fConst220 = (2.0f * (0.935140193f - fConst213));
		fConst221 = (2.0f * (0.935140193f - fConst188));
		fConst222 = std::tan((3141.59277f / fConst0));
		fConst223 = (1.0f / fConst222);
		fConst224 = (1.0f / (((fConst223 + 0.157482162f) / fConst222) + 0.935140193f));
		fConst225 = mydsp_faustpower2_f(fConst222);
		fConst226 = (50.0638084f / fConst225);
		fConst227 = (fConst226 + 0.935140193f);
		fConst228 = (1.0f / (((fConst223 + 0.743130445f) / fConst222) + 1.4500711f));
		fConst229 = (11.0520525f / fConst225);
		fConst230 = (fConst229 + 1.4500711f);
		fConst231 = (1.0f / (((fConst223 + 3.18972731f) / fConst222) + 4.07678175f));
		fConst232 = (0.00176617282f / fConst225);
		fConst233 = (fConst232 + 0.000407678192f);
		fConst234 = (1.0f / (((fConst185 + 0.168404877f) / fConst184) + 1.06935835f));
		fConst235 = (fConst213 + 53.5361519f);
		fConst236 = (1.0f / (((fConst185 + 0.51247865f) / fConst184) + 0.689621389f));
		fConst237 = (fConst213 + 7.62173128f);
		fConst238 = (1.0f / (((fConst185 + 0.782413065f) / fConst184) + 0.245291501f));
		fConst239 = (9.99999975e-05f / fConst187);
		fConst240 = (fConst239 + 0.000433227193f);
		fConst241 = (((fConst185 + -0.782413065f) / fConst184) + 0.245291501f);
		fConst242 = (2.0f * (0.245291501f - fConst213));
		fConst243 = (2.0f * (0.000433227193f - fConst239));
		fConst244 = (((fConst185 + -0.51247865f) / fConst184) + 0.689621389f);
		fConst245 = (2.0f * (0.689621389f - fConst213));
		fConst246 = (2.0f * (7.62173128f - fConst213));
		fConst247 = (((fConst185 + -0.168404877f) / fConst184) + 1.06935835f);
		fConst248 = (2.0f * (1.06935835f - fConst213));
		fConst249 = (2.0f * (53.5361519f - fConst213));
		fConst250 = (((fConst223 + -3.18972731f) / fConst222) + 4.07678175f);
		fConst251 = (1.0f / fConst225);
		fConst252 = (2.0f * (4.07678175f - fConst251));
		fConst253 = (2.0f * (0.000407678192f - fConst232));
		fConst254 = (((fConst223 + -0.743130445f) / fConst222) + 1.4500711f);
		fConst255 = (2.0f * (1.4500711f - fConst251));
		fConst256 = (2.0f * (1.4500711f - fConst229));
		fConst257 = (((fConst223 + -0.157482162f) / fConst222) + 0.935140193f);
		fConst258 = (2.0f * (0.935140193f - fConst251));
		fConst259 = (2.0f * (0.935140193f - fConst226));
		fConst260 = std::tan((1979.07935f / fConst0));
		fConst261 = (1.0f / fConst260);
		fConst262 = (1.0f / (((fConst261 + 0.157482162f) / fConst260) + 0.935140193f));
		fConst263 = mydsp_faustpower2_f(fConst260);
		fConst264 = (50.0638084f / fConst263);
		fConst265 = (fConst264 + 0.935140193f);
		fConst266 = (1.0f / (((fConst261 + 0.743130445f) / fConst260) + 1.4500711f));
		fConst267 = (11.0520525f / fConst263);
		fConst268 = (fConst267 + 1.4500711f);
		fConst269 = (1.0f / (((fConst261 + 3.18972731f) / fConst260) + 4.07678175f));
		fConst270 = (0.00176617282f / fConst263);
		fConst271 = (fConst270 + 0.000407678192f);
		fConst272 = (1.0f / (((fConst223 + 0.168404877f) / fConst222) + 1.06935835f));
		fConst273 = (fConst251 + 53.5361519f);
		fConst274 = (1.0f / (((fConst223 + 0.51247865f) / fConst222) + 0.689621389f));
		fConst275 = (fConst251 + 7.62173128f);
		fConst276 = (1.0f / (((fConst223 + 0.782413065f) / fConst222) + 0.245291501f));
		fConst277 = (9.99999975e-05f / fConst225);
		fConst278 = (fConst277 + 0.000433227193f);
		fConst279 = (((fConst223 + -0.782413065f) / fConst222) + 0.245291501f);
		fConst280 = (2.0f * (0.245291501f - fConst251));
		fConst281 = (2.0f * (0.000433227193f - fConst277));
		fConst282 = (((fConst223 + -0.51247865f) / fConst222) + 0.689621389f);
		fConst283 = (2.0f * (0.689621389f - fConst251));
		fConst284 = (2.0f * (7.62173128f - fConst251));
		fConst285 = (((fConst223 + -0.168404877f) / fConst222) + 1.06935835f);
		fConst286 = (2.0f * (1.06935835f - fConst251));
		fConst287 = (2.0f * (53.5361519f - fConst251));
		fConst288 = (((fConst261 + -3.18972731f) / fConst260) + 4.07678175f);
		fConst289 = (1.0f / fConst263);
		fConst290 = (2.0f * (4.07678175f - fConst289));
		fConst291 = (2.0f * (0.000407678192f - fConst270));
		fConst292 = (((fConst261 + -0.743130445f) / fConst260) + 1.4500711f);
		fConst293 = (2.0f * (1.4500711f - fConst289));
		fConst294 = (2.0f * (1.4500711f - fConst267));
		fConst295 = (((fConst261 + -0.157482162f) / fConst260) + 0.935140193f);
		fConst296 = (2.0f * (0.935140193f - fConst289));
		fConst297 = (2.0f * (0.935140193f - fConst264));
		fConst298 = std::tan((1246.74182f / fConst0));
		fConst299 = (1.0f / fConst298);
		fConst300 = (1.0f / (((fConst299 + 0.157482162f) / fConst298) + 0.935140193f));
		fConst301 = mydsp_faustpower2_f(fConst298);
		fConst302 = (50.0638084f / fConst301);
		fConst303 = (fConst302 + 0.935140193f);
		fConst304 = (1.0f / (((fConst299 + 0.743130445f) / fConst298) + 1.4500711f));
		fConst305 = (11.0520525f / fConst301);
		fConst306 = (fConst305 + 1.4500711f);
		fConst307 = (1.0f / (((fConst299 + 3.18972731f) / fConst298) + 4.07678175f));
		fConst308 = (0.00176617282f / fConst301);
		fConst309 = (fConst308 + 0.000407678192f);
		fConst310 = (1.0f / (((fConst261 + 0.168404877f) / fConst260) + 1.06935835f));
		fConst311 = (fConst289 + 53.5361519f);
		fConst312 = (1.0f / (((fConst261 + 0.51247865f) / fConst260) + 0.689621389f));
		fConst313 = (fConst289 + 7.62173128f);
		fConst314 = (1.0f / (((fConst261 + 0.782413065f) / fConst260) + 0.245291501f));
		fConst315 = (9.99999975e-05f / fConst263);
		fConst316 = (fConst315 + 0.000433227193f);
		fConst317 = (((fConst261 + -0.782413065f) / fConst260) + 0.245291501f);
		fConst318 = (2.0f * (0.245291501f - fConst289));
		fConst319 = (2.0f * (0.000433227193f - fConst315));
		fConst320 = (((fConst261 + -0.51247865f) / fConst260) + 0.689621389f);
		fConst321 = (2.0f * (0.689621389f - fConst289));
		fConst322 = (2.0f * (7.62173128f - fConst289));
		fConst323 = (((fConst261 + -0.168404877f) / fConst260) + 1.06935835f);
		fConst324 = (2.0f * (1.06935835f - fConst289));
		fConst325 = (2.0f * (53.5361519f - fConst289));
		fConst326 = (((fConst299 + -3.18972731f) / fConst298) + 4.07678175f);
		fConst327 = (1.0f / fConst301);
		fConst328 = (2.0f * (4.07678175f - fConst327));
		fConst329 = (2.0f * (0.000407678192f - fConst308));
		fConst330 = (((fConst299 + -0.743130445f) / fConst298) + 1.4500711f);
		fConst331 = (2.0f * (1.4500711f - fConst327));
		fConst332 = (2.0f * (1.4500711f - fConst305));
		fConst333 = (((fConst299 + -0.157482162f) / fConst298) + 0.935140193f);
		fConst334 = (2.0f * (0.935140193f - fConst327));
		fConst335 = (2.0f * (0.935140193f - fConst302));
		fConst336 = std::tan((785.398193f / fConst0));
		fConst337 = (1.0f / fConst336);
		fConst338 = (1.0f / (((fConst337 + 0.157482162f) / fConst336) + 0.935140193f));
		fConst339 = mydsp_faustpower2_f(fConst336);
		fConst340 = (50.0638084f / fConst339);
		fConst341 = (fConst340 + 0.935140193f);
		fConst342 = (1.0f / (((fConst337 + 0.743130445f) / fConst336) + 1.4500711f));
		fConst343 = (11.0520525f / fConst339);
		fConst344 = (fConst343 + 1.4500711f);
		fConst345 = (1.0f / (((fConst337 + 3.18972731f) / fConst336) + 4.07678175f));
		fConst346 = (0.00176617282f / fConst339);
		fConst347 = (fConst346 + 0.000407678192f);
		fConst348 = (1.0f / (((fConst299 + 0.168404877f) / fConst298) + 1.06935835f));
		fConst349 = (fConst327 + 53.5361519f);
		fConst350 = (1.0f / (((fConst299 + 0.51247865f) / fConst298) + 0.689621389f));
		fConst351 = (fConst327 + 7.62173128f);
		fConst352 = (1.0f / (((fConst299 + 0.782413065f) / fConst298) + 0.245291501f));
		fConst353 = (9.99999975e-05f / fConst301);
		fConst354 = (fConst353 + 0.000433227193f);
		fConst355 = (((fConst299 + -0.782413065f) / fConst298) + 0.245291501f);
		fConst356 = (2.0f * (0.245291501f - fConst327));
		fConst357 = (2.0f * (0.000433227193f - fConst353));
		fConst358 = (((fConst299 + -0.51247865f) / fConst298) + 0.689621389f);
		fConst359 = (2.0f * (0.689621389f - fConst327));
		fConst360 = (2.0f * (7.62173128f - fConst327));
		fConst361 = (((fConst299 + -0.168404877f) / fConst298) + 1.06935835f);
		fConst362 = (2.0f * (1.06935835f - fConst327));
		fConst363 = (2.0f * (53.5361519f - fConst327));
		fConst364 = (((fConst337 + -3.18972731f) / fConst336) + 4.07678175f);
		fConst365 = (1.0f / fConst339);
		fConst366 = (2.0f * (4.07678175f - fConst365));
		fConst367 = (2.0f * (0.000407678192f - fConst346));
		fConst368 = (((fConst337 + -0.743130445f) / fConst336) + 1.4500711f);
		fConst369 = (2.0f * (1.4500711f - fConst365));
		fConst370 = (2.0f * (1.4500711f - fConst343));
		fConst371 = (((fConst337 + -0.157482162f) / fConst336) + 0.935140193f);
		fConst372 = (2.0f * (0.935140193f - fConst365));
		fConst373 = (2.0f * (0.935140193f - fConst340));
		fConst374 = std::tan((494.769836f / fConst0));
		fConst375 = (1.0f / fConst374);
		fConst376 = (1.0f / (((fConst375 + 0.157482162f) / fConst374) + 0.935140193f));
		fConst377 = mydsp_faustpower2_f(fConst374);
		fConst378 = (50.0638084f / fConst377);
		fConst379 = (fConst378 + 0.935140193f);
		fConst380 = (1.0f / (((fConst375 + 0.743130445f) / fConst374) + 1.4500711f));
		fConst381 = (11.0520525f / fConst377);
		fConst382 = (fConst381 + 1.4500711f);
		fConst383 = (1.0f / (((fConst375 + 3.18972731f) / fConst374) + 4.07678175f));
		fConst384 = (0.00176617282f / fConst377);
		fConst385 = (fConst384 + 0.000407678192f);
		fConst386 = (1.0f / (((fConst337 + 0.168404877f) / fConst336) + 1.06935835f));
		fConst387 = (fConst365 + 53.5361519f);
		fConst388 = (1.0f / (((fConst337 + 0.51247865f) / fConst336) + 0.689621389f));
		fConst389 = (fConst365 + 7.62173128f);
		fConst390 = (1.0f / (((fConst337 + 0.782413065f) / fConst336) + 0.245291501f));
		fConst391 = (9.99999975e-05f / fConst339);
		fConst392 = (fConst391 + 0.000433227193f);
		fConst393 = (((fConst337 + -0.782413065f) / fConst336) + 0.245291501f);
		fConst394 = (2.0f * (0.245291501f - fConst365));
		fConst395 = (2.0f * (0.000433227193f - fConst391));
		fConst396 = (((fConst337 + -0.51247865f) / fConst336) + 0.689621389f);
		fConst397 = (2.0f * (0.689621389f - fConst365));
		fConst398 = (2.0f * (7.62173128f - fConst365));
		fConst399 = (((fConst337 + -0.168404877f) / fConst336) + 1.06935835f);
		fConst400 = (2.0f * (1.06935835f - fConst365));
		fConst401 = (2.0f * (53.5361519f - fConst365));
		fConst402 = (((fConst375 + -3.18972731f) / fConst374) + 4.07678175f);
		fConst403 = (1.0f / fConst377);
		fConst404 = (2.0f * (4.07678175f - fConst403));
		fConst405 = (2.0f * (0.000407678192f - fConst384));
		fConst406 = (((fConst375 + -0.743130445f) / fConst374) + 1.4500711f);
		fConst407 = (2.0f * (1.4500711f - fConst403));
		fConst408 = (2.0f * (1.4500711f - fConst381));
		fConst409 = (((fConst375 + -0.157482162f) / fConst374) + 0.935140193f);
		fConst410 = (2.0f * (0.935140193f - fConst403));
		fConst411 = (2.0f * (0.935140193f - fConst378));
		fConst412 = std::tan((311.685455f / fConst0));
		fConst413 = (1.0f / fConst412);
		fConst414 = (1.0f / (((fConst413 + 0.157482162f) / fConst412) + 0.935140193f));
		fConst415 = mydsp_faustpower2_f(fConst412);
		fConst416 = (50.0638084f / fConst415);
		fConst417 = (fConst416 + 0.935140193f);
		fConst418 = (1.0f / (((fConst413 + 0.743130445f) / fConst412) + 1.4500711f));
		fConst419 = (11.0520525f / fConst415);
		fConst420 = (fConst419 + 1.4500711f);
		fConst421 = (1.0f / (((fConst413 + 3.18972731f) / fConst412) + 4.07678175f));
		fConst422 = (0.00176617282f / fConst415);
		fConst423 = (fConst422 + 0.000407678192f);
		fConst424 = (1.0f / (((fConst375 + 0.168404877f) / fConst374) + 1.06935835f));
		fConst425 = (fConst403 + 53.5361519f);
		fConst426 = (1.0f / (((fConst375 + 0.51247865f) / fConst374) + 0.689621389f));
		fConst427 = (fConst403 + 7.62173128f);
		fConst428 = (1.0f / (((fConst375 + 0.782413065f) / fConst374) + 0.245291501f));
		fConst429 = (9.99999975e-05f / fConst377);
		fConst430 = (fConst429 + 0.000433227193f);
		fConst431 = (((fConst375 + -0.782413065f) / fConst374) + 0.245291501f);
		fConst432 = (2.0f * (0.245291501f - fConst403));
		fConst433 = (2.0f * (0.000433227193f - fConst429));
		fConst434 = (((fConst375 + -0.51247865f) / fConst374) + 0.689621389f);
		fConst435 = (2.0f * (0.689621389f - fConst403));
		fConst436 = (2.0f * (7.62173128f - fConst403));
		fConst437 = (((fConst375 + -0.168404877f) / fConst374) + 1.06935835f);
		fConst438 = (2.0f * (1.06935835f - fConst403));
		fConst439 = (2.0f * (53.5361519f - fConst403));
		fConst440 = (((fConst413 + -3.18972731f) / fConst412) + 4.07678175f);
		fConst441 = (1.0f / fConst415);
		fConst442 = (2.0f * (4.07678175f - fConst441));
		fConst443 = (2.0f * (0.000407678192f - fConst422));
		fConst444 = (((fConst413 + -0.743130445f) / fConst412) + 1.4500711f);
		fConst445 = (2.0f * (1.4500711f - fConst441));
		fConst446 = (2.0f * (1.4500711f - fConst419));
		fConst447 = (((fConst413 + -0.157482162f) / fConst412) + 0.935140193f);
		fConst448 = (2.0f * (0.935140193f - fConst441));
		fConst449 = (2.0f * (0.935140193f - fConst416));
		fConst450 = std::tan((196.349548f / fConst0));
		fConst451 = (1.0f / fConst450);
		fConst452 = (1.0f / (((fConst451 + 0.157482162f) / fConst450) + 0.935140193f));
		fConst453 = mydsp_faustpower2_f(fConst450);
		fConst454 = (50.0638084f / fConst453);
		fConst455 = (fConst454 + 0.935140193f);
		fConst456 = (1.0f / (((fConst451 + 0.743130445f) / fConst450) + 1.4500711f));
		fConst457 = (11.0520525f / fConst453);
		fConst458 = (fConst457 + 1.4500711f);
		fConst459 = (1.0f / (((fConst451 + 3.18972731f) / fConst450) + 4.07678175f));
		fConst460 = (0.00176617282f / fConst453);
		fConst461 = (fConst460 + 0.000407678192f);
		fConst462 = (1.0f / (((fConst413 + 0.168404877f) / fConst412) + 1.06935835f));
		fConst463 = (fConst441 + 53.5361519f);
		fConst464 = (1.0f / (((fConst413 + 0.51247865f) / fConst412) + 0.689621389f));
		fConst465 = (fConst441 + 7.62173128f);
		fConst466 = (1.0f / (((fConst413 + 0.782413065f) / fConst412) + 0.245291501f));
		fConst467 = (9.99999975e-05f / fConst415);
		fConst468 = (fConst467 + 0.000433227193f);
		fConst469 = (((fConst413 + -0.782413065f) / fConst412) + 0.245291501f);
		fConst470 = (2.0f * (0.245291501f - fConst441));
		fConst471 = (2.0f * (0.000433227193f - fConst467));
		fConst472 = (((fConst413 + -0.51247865f) / fConst412) + 0.689621389f);
		fConst473 = (2.0f * (0.689621389f - fConst441));
		fConst474 = (2.0f * (7.62173128f - fConst441));
		fConst475 = (((fConst413 + -0.168404877f) / fConst412) + 1.06935835f);
		fConst476 = (2.0f * (1.06935835f - fConst441));
		fConst477 = (2.0f * (53.5361519f - fConst441));
		fConst478 = (((fConst451 + -3.18972731f) / fConst450) + 4.07678175f);
		fConst479 = (1.0f / fConst453);
		fConst480 = (2.0f * (4.07678175f - fConst479));
		fConst481 = (2.0f * (0.000407678192f - fConst460));
		fConst482 = (((fConst451 + -0.743130445f) / fConst450) + 1.4500711f);
		fConst483 = (2.0f * (1.4500711f - fConst479));
		fConst484 = (2.0f * (1.4500711f - fConst457));
		fConst485 = (((fConst451 + -0.157482162f) / fConst450) + 0.935140193f);
		fConst486 = (2.0f * (0.935140193f - fConst479));
		fConst487 = (2.0f * (0.935140193f - fConst454));
		fConst488 = std::tan((123.692459f / fConst0));
		fConst489 = (1.0f / fConst488);
		fConst490 = (1.0f / (((fConst489 + 0.157482162f) / fConst488) + 0.935140193f));
		fConst491 = mydsp_faustpower2_f(fConst488);
		fConst492 = (50.0638084f / fConst491);
		fConst493 = (fConst492 + 0.935140193f);
		fConst494 = (1.0f / (((fConst489 + 0.743130445f) / fConst488) + 1.4500711f));
		fConst495 = (11.0520525f / fConst491);
		fConst496 = (fConst495 + 1.4500711f);
		fConst497 = (1.0f / (((fConst489 + 3.18972731f) / fConst488) + 4.07678175f));
		fConst498 = (0.00176617282f / fConst491);
		fConst499 = (fConst498 + 0.000407678192f);
		fConst500 = (1.0f / (((fConst451 + 0.168404877f) / fConst450) + 1.06935835f));
		fConst501 = (fConst479 + 53.5361519f);
		fConst502 = (1.0f / (((fConst451 + 0.51247865f) / fConst450) + 0.689621389f));
		fConst503 = (fConst479 + 7.62173128f);
		fConst504 = (1.0f / (((fConst451 + 0.782413065f) / fConst450) + 0.245291501f));
		fConst505 = (9.99999975e-05f / fConst453);
		fConst506 = (fConst505 + 0.000433227193f);
		fConst507 = (((fConst451 + -0.782413065f) / fConst450) + 0.245291501f);
		fConst508 = (2.0f * (0.245291501f - fConst479));
		fConst509 = (2.0f * (0.000433227193f - fConst505));
		fConst510 = (((fConst451 + -0.51247865f) / fConst450) + 0.689621389f);
		fConst511 = (2.0f * (0.689621389f - fConst479));
		fConst512 = (2.0f * (7.62173128f - fConst479));
		fConst513 = (((fConst451 + -0.168404877f) / fConst450) + 1.06935835f);
		fConst514 = (2.0f * (1.06935835f - fConst479));
		fConst515 = (2.0f * (53.5361519f - fConst479));
		fConst516 = (((fConst489 + -3.18972731f) / fConst488) + 4.07678175f);
		fConst517 = (1.0f / fConst491);
		fConst518 = (2.0f * (4.07678175f - fConst517));
		fConst519 = (2.0f * (0.000407678192f - fConst498));
		fConst520 = (((fConst489 + -0.743130445f) / fConst488) + 1.4500711f);
		fConst521 = (2.0f * (1.4500711f - fConst517));
		fConst522 = (2.0f * (1.4500711f - fConst495));
		fConst523 = (((fConst489 + -0.157482162f) / fConst488) + 0.935140193f);
		fConst524 = (2.0f * (0.935140193f - fConst517));
		fConst525 = (2.0f * (0.935140193f - fConst492));
		fConst526 = (1.0f / (((fConst489 + 0.168404877f) / fConst488) + 1.06935835f));
		fConst527 = (fConst517 + 53.5361519f);
		fConst528 = (1.0f / (((fConst489 + 0.51247865f) / fConst488) + 0.689621389f));
		fConst529 = (fConst517 + 7.62173128f);
		fConst530 = (1.0f / (((fConst489 + 0.782413065f) / fConst488) + 0.245291501f));
		fConst531 = (9.99999975e-05f / fConst491);
		fConst532 = (fConst531 + 0.000433227193f);
		fConst533 = (((fConst489 + -0.782413065f) / fConst488) + 0.245291501f);
		fConst534 = (2.0f * (0.245291501f - fConst517));
		fConst535 = (2.0f * (0.000433227193f - fConst531));
		fConst536 = (((fConst489 + -0.51247865f) / fConst488) + 0.689621389f);
		fConst537 = (2.0f * (0.689621389f - fConst517));
		fConst538 = (2.0f * (7.62173128f - fConst517));
		fConst539 = (((fConst489 + -0.168404877f) / fConst488) + 1.06935835f);
		fConst540 = (2.0f * (1.06935835f - fConst517));
		fConst541 = (2.0f * (53.5361519f - fConst517));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(50.0f);
		fHslider1 = FAUSTFLOAT(100.0f);
		fVslider0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(-20.0f);
		fVslider1 = FAUSTFLOAT(1.0f);
		fEntry0 = FAUSTFLOAT(2.0f);
		fHslider3 = FAUSTFLOAT(49.0f);
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
			fRec4[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec6[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
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
			fRec7[l12] = 0.0f;
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
			fRec8[l20] = 0.0f;
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
			fRec9[l28] = 0.0f;
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
			fRec10[l32] = 0.0f;
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
			fRec11[l36] = 0.0f;
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fVec29[l37] = 0.0f;
		}
		for (int l38 = 0; (l38 < 4096); l38 = (l38 + 1)) {
			fVec30[l38] = 0.0f;
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec12[l39] = 0.0f;
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec13[l40] = 0.0f;
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec14[l41] = 0.0f;
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
			fRec15[l45] = 0.0f;
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
			iRec17[l52] = 0;
		}
		for (int l53 = 0; (l53 < 4); l53 = (l53 + 1)) {
			fRec16[l53] = 0.0f;
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec3[l54] = 0.0f;
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec2[l55] = 0.0f;
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec1[l56] = 0.0f;
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec0[l57] = 0.0f;
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec24[l58] = 0.0f;
		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec23[l59] = 0.0f;
		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec22[l60] = 0.0f;
		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec21[l61] = 0.0f;
		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec20[l62] = 0.0f;
		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec19[l63] = 0.0f;
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec18[l64] = 0.0f;
		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec31[l65] = 0.0f;
		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec30[l66] = 0.0f;
		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec29[l67] = 0.0f;
		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec28[l68] = 0.0f;
		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec27[l69] = 0.0f;
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec26[l70] = 0.0f;
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec25[l71] = 0.0f;
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec38[l72] = 0.0f;
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec37[l73] = 0.0f;
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec36[l74] = 0.0f;
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec35[l75] = 0.0f;
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec34[l76] = 0.0f;
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec33[l77] = 0.0f;
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			fRec32[l78] = 0.0f;
		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec45[l79] = 0.0f;
		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec44[l80] = 0.0f;
		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec43[l81] = 0.0f;
		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec42[l82] = 0.0f;
		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec41[l83] = 0.0f;
		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec40[l84] = 0.0f;
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fRec39[l85] = 0.0f;
		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec52[l86] = 0.0f;
		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec51[l87] = 0.0f;
		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec50[l88] = 0.0f;
		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec49[l89] = 0.0f;
		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec48[l90] = 0.0f;
		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec47[l91] = 0.0f;
		}
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			fRec46[l92] = 0.0f;
		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec59[l93] = 0.0f;
		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec58[l94] = 0.0f;
		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec57[l95] = 0.0f;
		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec56[l96] = 0.0f;
		}
		for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			fRec55[l97] = 0.0f;
		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec54[l98] = 0.0f;
		}
		for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			fRec53[l99] = 0.0f;
		}
		for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			fRec66[l100] = 0.0f;
		}
		for (int l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			fRec65[l101] = 0.0f;
		}
		for (int l102 = 0; (l102 < 3); l102 = (l102 + 1)) {
			fRec64[l102] = 0.0f;
		}
		for (int l103 = 0; (l103 < 3); l103 = (l103 + 1)) {
			fRec63[l103] = 0.0f;
		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec62[l104] = 0.0f;
		}
		for (int l105 = 0; (l105 < 3); l105 = (l105 + 1)) {
			fRec61[l105] = 0.0f;
		}
		for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			fRec60[l106] = 0.0f;
		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec73[l107] = 0.0f;
		}
		for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			fRec72[l108] = 0.0f;
		}
		for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			fRec71[l109] = 0.0f;
		}
		for (int l110 = 0; (l110 < 3); l110 = (l110 + 1)) {
			fRec70[l110] = 0.0f;
		}
		for (int l111 = 0; (l111 < 3); l111 = (l111 + 1)) {
			fRec69[l111] = 0.0f;
		}
		for (int l112 = 0; (l112 < 3); l112 = (l112 + 1)) {
			fRec68[l112] = 0.0f;
		}
		for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			fRec67[l113] = 0.0f;
		}
		for (int l114 = 0; (l114 < 3); l114 = (l114 + 1)) {
			fRec80[l114] = 0.0f;
		}
		for (int l115 = 0; (l115 < 3); l115 = (l115 + 1)) {
			fRec79[l115] = 0.0f;
		}
		for (int l116 = 0; (l116 < 3); l116 = (l116 + 1)) {
			fRec78[l116] = 0.0f;
		}
		for (int l117 = 0; (l117 < 3); l117 = (l117 + 1)) {
			fRec77[l117] = 0.0f;
		}
		for (int l118 = 0; (l118 < 3); l118 = (l118 + 1)) {
			fRec76[l118] = 0.0f;
		}
		for (int l119 = 0; (l119 < 3); l119 = (l119 + 1)) {
			fRec75[l119] = 0.0f;
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			fRec74[l120] = 0.0f;
		}
		for (int l121 = 0; (l121 < 3); l121 = (l121 + 1)) {
			fRec87[l121] = 0.0f;
		}
		for (int l122 = 0; (l122 < 3); l122 = (l122 + 1)) {
			fRec86[l122] = 0.0f;
		}
		for (int l123 = 0; (l123 < 3); l123 = (l123 + 1)) {
			fRec85[l123] = 0.0f;
		}
		for (int l124 = 0; (l124 < 3); l124 = (l124 + 1)) {
			fRec84[l124] = 0.0f;
		}
		for (int l125 = 0; (l125 < 3); l125 = (l125 + 1)) {
			fRec83[l125] = 0.0f;
		}
		for (int l126 = 0; (l126 < 3); l126 = (l126 + 1)) {
			fRec82[l126] = 0.0f;
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			fRec81[l127] = 0.0f;
		}
		for (int l128 = 0; (l128 < 3); l128 = (l128 + 1)) {
			fRec94[l128] = 0.0f;
		}
		for (int l129 = 0; (l129 < 3); l129 = (l129 + 1)) {
			fRec93[l129] = 0.0f;
		}
		for (int l130 = 0; (l130 < 3); l130 = (l130 + 1)) {
			fRec92[l130] = 0.0f;
		}
		for (int l131 = 0; (l131 < 3); l131 = (l131 + 1)) {
			fRec91[l131] = 0.0f;
		}
		for (int l132 = 0; (l132 < 3); l132 = (l132 + 1)) {
			fRec90[l132] = 0.0f;
		}
		for (int l133 = 0; (l133 < 3); l133 = (l133 + 1)) {
			fRec89[l133] = 0.0f;
		}
		for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			fRec88[l134] = 0.0f;
		}
		for (int l135 = 0; (l135 < 3); l135 = (l135 + 1)) {
			fRec101[l135] = 0.0f;
		}
		for (int l136 = 0; (l136 < 3); l136 = (l136 + 1)) {
			fRec100[l136] = 0.0f;
		}
		for (int l137 = 0; (l137 < 3); l137 = (l137 + 1)) {
			fRec99[l137] = 0.0f;
		}
		for (int l138 = 0; (l138 < 3); l138 = (l138 + 1)) {
			fRec98[l138] = 0.0f;
		}
		for (int l139 = 0; (l139 < 3); l139 = (l139 + 1)) {
			fRec97[l139] = 0.0f;
		}
		for (int l140 = 0; (l140 < 3); l140 = (l140 + 1)) {
			fRec96[l140] = 0.0f;
		}
		for (int l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			fRec95[l141] = 0.0f;
		}
		for (int l142 = 0; (l142 < 3); l142 = (l142 + 1)) {
			fRec108[l142] = 0.0f;
		}
		for (int l143 = 0; (l143 < 3); l143 = (l143 + 1)) {
			fRec107[l143] = 0.0f;
		}
		for (int l144 = 0; (l144 < 3); l144 = (l144 + 1)) {
			fRec106[l144] = 0.0f;
		}
		for (int l145 = 0; (l145 < 3); l145 = (l145 + 1)) {
			fRec105[l145] = 0.0f;
		}
		for (int l146 = 0; (l146 < 3); l146 = (l146 + 1)) {
			fRec104[l146] = 0.0f;
		}
		for (int l147 = 0; (l147 < 3); l147 = (l147 + 1)) {
			fRec103[l147] = 0.0f;
		}
		for (int l148 = 0; (l148 < 2); l148 = (l148 + 1)) {
			fRec102[l148] = 0.0f;
		}
		for (int l149 = 0; (l149 < 3); l149 = (l149 + 1)) {
			fRec112[l149] = 0.0f;
		}
		for (int l150 = 0; (l150 < 3); l150 = (l150 + 1)) {
			fRec111[l150] = 0.0f;
		}
		for (int l151 = 0; (l151 < 3); l151 = (l151 + 1)) {
			fRec110[l151] = 0.0f;
		}
		for (int l152 = 0; (l152 < 2); l152 = (l152 + 1)) {
			fRec109[l152] = 0.0f;
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
		ui_interface->openVerticalBox("virtualAnalogLab");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("0x00");
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
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "style", "hslider");
		ui_interface->declare(&fHslider2, "tooltip", "Sawtooth waveform amplitude");
		ui_interface->declare(&fHslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("Mix Amplitude", &fHslider2, -20.0f, -120.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->declare(&fHslider3, "style", "hslider");
		ui_interface->declare(&fHslider3, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)");
		ui_interface->declare(&fHslider3, "unit", "PK");
		ui_interface->addHorizontalSlider("Frequency", &fHslider3, 49.0f, 1.0f, 88.0f, 0.00999999978f);
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
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filters.lib for documentation and references");
		ui_interface->openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning    LP, 9 octaves below 16000 Hz, HP");
		ui_interface->declare(&fVbargraph14, "0", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph14, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c582bccf0", &fVbargraph14, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph13, "1", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph13, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c582a8f70", &fVbargraph13, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph12, "2", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph12, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c582828a0", &fVbargraph12, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph11, "3", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph11, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c5825c1d0", &fVbargraph11, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph10, "4", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph10, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c58235b00", &fVbargraph10, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph9, "5", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph9, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c5820f430", &fVbargraph9, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph8, "6", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph8, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c581e8d60", &fVbargraph8, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph7, "7", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c581c2690", &fVbargraph7, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph6, "8", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c5819bfc0", &fVbargraph6, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph5, "9", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c581758f0", &fVbargraph5, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph4, "10", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c5814f220", &fVbargraph4, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph3, "11", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c58128b50", &fVbargraph3, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph2, "12", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c58102480", &fVbargraph2, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph1, "13", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c580dbdb0", &fVbargraph1, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph0, "14", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x563c580b3e60", &fVbargraph0, -50.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("SPECTRUM ANALYZER CONTROLS");
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "tooltip", "band-level averaging time in milliseconds");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Level Averaging Time", &fHslider1, 100.0f, 1.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "tooltip", "Level offset in decibels");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Level dB Offset", &fHslider0, 50.0f, -50.0f, 100.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		float fSlow1 = std::exp((0.0f - (fConst1 / float(fHslider1))));
		float fSlow2 = (1.0f - fSlow1);
		float fSlow3 = float(fVslider0);
		float fSlow4 = (0.00100000005f * std::pow(10.0f, (0.0500000007f * float(fHslider2))));
		float fSlow5 = (0.333333343f * float(fVslider1));
		int iSlow6 = int((float(fEntry0) + -1.0f));
		int iSlow7 = (iSlow6 >= 2);
		int iSlow8 = (iSlow6 >= 1);
		float fSlow9 = std::exp((0.0f - (fConst14 / float(fVslider2))));
		float fSlow10 = (440.0f * (std::pow(2.0f, (0.0833333358f * (float(fHslider3) + -49.0f))) * (1.0f - fSlow9)));
		int iSlow11 = (iSlow6 >= 3);
		float fSlow12 = (1.0f - (0.00999999978f * float(fVslider3)));
		float fSlow13 = ((0.00999999978f * float(fVslider4)) + 1.0f);
		float fSlow14 = (fConst18 * float(fVslider5));
		float fSlow15 = (fConst20 * float(fVslider6));
		float fSlow16 = (fConst0 * float(fVslider7));
		float fSlow17 = float(fCheckbox0);
		float fSlow18 = (fConst21 * fSlow17);
		float fSlow19 = (0.00999999978f * float(fVslider8));
		float fSlow20 = (0.0833333358f * (1.0f - fSlow17));
		float fSlow21 = float(fVslider9);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec4[0] = (fSlow4 + (0.999000013f * fRec4[1]));
			fRec6[0] = (fSlow10 + (fSlow9 * fRec6[1]));
			float fTemp0 = std::max<float>(20.0f, std::fabs(fRec6[0]));
			fVec1[0] = fTemp0;
			float fTemp1 = (fRec5[1] + (fConst14 * fVec1[1]));
			fRec5[0] = (fTemp1 - std::floor(fTemp1));
			float fTemp2 = (2.0f * fRec5[0]);
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
			float fTemp13 = (fSlow12 * fRec6[0]);
			float fTemp14 = std::max<float>(20.0f, std::fabs(fTemp13));
			fVec8[0] = fTemp14;
			float fTemp15 = (fRec7[1] + (fConst14 * fVec8[1]));
			fRec7[0] = (fTemp15 - std::floor(fTemp15));
			float fTemp16 = (2.0f * fRec7[0]);
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
			float fTemp24 = (fSlow13 * fRec6[0]);
			float fTemp25 = std::max<float>(20.0f, std::fabs(fTemp24));
			fVec15[0] = fTemp25;
			float fTemp26 = (fRec8[1] + (fConst14 * fVec15[1]));
			fRec8[0] = (fTemp26 - std::floor(fTemp26));
			float fTemp27 = (2.0f * fRec8[0]);
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
			float fTemp35 = std::max<float>(fRec6[0], 23.4489498f);
			float fTemp36 = std::max<float>(20.0f, std::fabs(fTemp35));
			fVec22[0] = fTemp36;
			float fTemp37 = (fRec9[1] + (fConst14 * fVec22[1]));
			fRec9[0] = (fTemp37 - std::floor(fTemp37));
			float fTemp38 = (2.0f * fRec9[0]);
			float fTemp39 = (fTemp38 + -1.0f);
			float fTemp40 = mydsp_faustpower2_f(fTemp39);
			fVec23[0] = fTemp40;
			float fTemp41 = ((fTemp4 * (fTemp40 - fVec23[1])) / fTemp36);
			fVec24[(IOTA & 4095)] = fTemp41;
			float fTemp42 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst19 / fTemp35)));
			int iTemp43 = int(fTemp42);
			float fTemp44 = std::floor(fTemp42);
			float fTemp45 = ((fTemp41 - (fVec24[((IOTA - iTemp43) & 4095)] * (fTemp44 + (1.0f - fTemp42)))) - ((fTemp42 - fTemp44) * fVec24[((IOTA - (iTemp43 + 1)) & 4095)]));
			float fTemp46 = std::max<float>(fTemp13, 23.4489498f);
			float fTemp47 = std::max<float>(20.0f, std::fabs(fTemp46));
			fVec25[0] = fTemp47;
			float fTemp48 = (fRec10[1] + (fConst14 * fVec25[1]));
			fRec10[0] = (fTemp48 - std::floor(fTemp48));
			float fTemp49 = (2.0f * fRec10[0]);
			float fTemp50 = (fTemp49 + -1.0f);
			float fTemp51 = mydsp_faustpower2_f(fTemp50);
			fVec26[0] = fTemp51;
			float fTemp52 = ((fTemp4 * (fTemp51 - fVec26[1])) / fTemp47);
			fVec27[(IOTA & 4095)] = fTemp52;
			float fTemp53 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst19 / fTemp46)));
			int iTemp54 = int(fTemp53);
			float fTemp55 = std::floor(fTemp53);
			float fTemp56 = ((fTemp52 - (fVec27[((IOTA - iTemp54) & 4095)] * (fTemp55 + (1.0f - fTemp53)))) - ((fTemp53 - fTemp55) * fVec27[((IOTA - (iTemp54 + 1)) & 4095)]));
			float fTemp57 = std::max<float>(fTemp24, 23.4489498f);
			float fTemp58 = std::max<float>(20.0f, std::fabs(fTemp57));
			fVec28[0] = fTemp58;
			float fTemp59 = (fRec11[1] + (fConst14 * fVec28[1]));
			fRec11[0] = (fTemp59 - std::floor(fTemp59));
			float fTemp60 = (2.0f * fRec11[0]);
			float fTemp61 = (fTemp60 + -1.0f);
			float fTemp62 = mydsp_faustpower2_f(fTemp61);
			fVec29[0] = fTemp62;
			float fTemp63 = ((fTemp4 * (fTemp62 - fVec29[1])) / fTemp58);
			fVec30[(IOTA & 4095)] = fTemp63;
			float fTemp64 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst19 / fTemp57)));
			int iTemp65 = int(fTemp64);
			float fTemp66 = std::floor(fTemp64);
			float fTemp67 = ((fTemp63 - (fVec30[((IOTA - iTemp65) & 4095)] * (fTemp66 + (1.0f - fTemp64)))) - ((fTemp64 - fTemp66) * fVec30[((IOTA - (iTemp65 + 1)) & 4095)]));
			fRec12[0] = ((fConst15 * fTemp45) + (0.999000013f * fRec12[1]));
			fRec13[0] = ((fConst15 * fTemp56) + (0.999000013f * fRec13[1]));
			fRec14[0] = ((fConst15 * fTemp67) + (0.999000013f * fRec14[1]));
			float fTemp68 = mydsp_faustpower3_f(fTemp39);
			fVec31[0] = (fTemp68 + (1.0f - fTemp38));
			float fTemp69 = ((fTemp68 + (1.0f - (fTemp38 + fVec31[1]))) / fTemp36);
			fVec32[0] = fTemp69;
			float fTemp70 = ((fTemp6 * (fTemp69 - fVec32[1])) / fTemp36);
			fVec33[(IOTA & 4095)] = fTemp70;
			fRec15[0] = (fSlow19 + (0.99000001f * fRec15[1]));
			float fTemp71 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst0 * (fRec15[0] / fTemp35))));
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
			float fTemp80 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst0 * (fRec15[0] / fTemp46))));
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
			float fTemp89 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst0 * (fRec15[0] / fTemp57))));
			int iTemp90 = int(fTemp89);
			float fTemp91 = std::floor(fTemp89);
			float fTemp92 = (fTemp91 + (1.0f - fTemp89));
			float fTemp93 = (fTemp89 - fTemp91);
			int iTemp94 = (iTemp90 + 1);
			iRec17[0] = ((1103515245 * iRec17[1]) + 12345);
			fRec16[0] = (((0.522189379f * fRec16[3]) + ((4.65661287e-10f * float(iRec17[0])) + (2.49495602f * fRec16[1]))) - (2.0172658f * fRec16[2]));
			float fTemp95 = ((fSlow3 * float(input0[i])) + (fRec4[0] * (((((fSlow5 * (((iSlow7 ? (iSlow11 ? (fConst17 * ((fTemp9 * (fTemp12 - fVec7[1])) / fTemp0)) : (fConst16 * ((fTemp6 * (fTemp8 - fVec4[1])) / fTemp0))) : (iSlow8 ? (fConst15 * ((fTemp4 * (fTemp5 - fVec2[1])) / fTemp0)) : fTemp3)) + (iSlow7 ? (iSlow11 ? (fConst17 * ((fTemp9 * (fTemp23 - fVec14[1])) / fTemp14)) : (fConst16 * ((fTemp6 * (fTemp20 - fVec11[1])) / fTemp14))) : (iSlow8 ? (fConst15 * ((fTemp4 * (fTemp18 - fVec9[1])) / fTemp14)) : fTemp17))) + (iSlow7 ? (iSlow11 ? (fConst17 * ((fTemp9 * (fTemp34 - fVec21[1])) / fTemp25)) : (fConst16 * ((fTemp6 * (fTemp31 - fVec18[1])) / fTemp25))) : (iSlow8 ? (fConst15 * ((fTemp4 * (fTemp29 - fVec16[1])) / fTemp25)) : fTemp28)))) + (fSlow14 * ((fTemp45 + fTemp56) + fTemp67))) + (fSlow15 * (fRec6[0] * ((fRec12[0] + (fSlow12 * fRec13[0])) + (fSlow13 * fRec14[0]))))) + (fSlow16 * ((fSlow18 * ((((fTemp70 - (fVec33[((IOTA - iTemp72) & 4095)] * fTemp74)) - (fTemp75 * fVec33[((IOTA - iTemp76) & 4095)])) + ((fTemp79 - (fVec36[((IOTA - iTemp81) & 4095)] * fTemp83)) - (fTemp84 * fVec36[((IOTA - iTemp85) & 4095)]))) + ((fTemp88 - (fVec39[((IOTA - iTemp90) & 4095)] * fTemp92)) - (fTemp93 * fVec39[((IOTA - iTemp94) & 4095)])))) + (fSlow20 * ((((fTemp41 - (fTemp74 * fVec24[((IOTA - iTemp72) & 4095)])) - (fTemp75 * fVec24[((IOTA - iTemp76) & 4095)])) + ((fTemp52 - (fTemp83 * fVec27[((IOTA - iTemp81) & 4095)])) - (fTemp84 * fVec27[((IOTA - iTemp85) & 4095)]))) + ((fTemp63 - (fTemp92 * fVec30[((IOTA - iTemp90) & 4095)])) - (fTemp93 * fVec30[((IOTA - iTemp94) & 4095)]))))))) + (fSlow21 * (((0.0499220341f * fRec16[0]) + (0.0506126992f * fRec16[2])) - ((0.0959935337f * fRec16[1]) + (0.00440878607f * fRec16[3])))))));
			fRec3[0] = (fTemp95 - (fConst11 * ((fConst22 * fRec3[2]) + (fConst24 * fRec3[1]))));
			fRec2[0] = ((fConst11 * (((fConst13 * fRec3[0]) + (fConst25 * fRec3[1])) + (fConst13 * fRec3[2]))) - (fConst8 * ((fConst26 * fRec2[2]) + (fConst27 * fRec2[1]))));
			fRec1[0] = ((fConst8 * (((fConst10 * fRec2[0]) + (fConst28 * fRec2[1])) + (fConst10 * fRec2[2]))) - (fConst4 * ((fConst29 * fRec1[2]) + (fConst30 * fRec1[1]))));
			fRec0[0] = ((fSlow1 * fRec0[1]) + (fSlow2 * std::fabs((fConst4 * (((fConst7 * fRec1[0]) + (fConst31 * fRec1[1])) + (fConst7 * fRec1[2]))))));
			fVbargraph0 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec0[0])))));
			fRec24[0] = (fTemp95 - (fConst48 * ((fConst51 * fRec24[2]) + (fConst52 * fRec24[1]))));
			fRec23[0] = ((fConst48 * (((fConst50 * fRec24[0]) + (fConst53 * fRec24[1])) + (fConst50 * fRec24[2]))) - (fConst46 * ((fConst54 * fRec23[2]) + (fConst55 * fRec23[1]))));
			fRec22[0] = ((fConst46 * (((fConst47 * fRec23[0]) + (fConst56 * fRec23[1])) + (fConst47 * fRec23[2]))) - (fConst44 * ((fConst57 * fRec22[2]) + (fConst58 * fRec22[1]))));
			float fTemp96 = (fConst44 * (((fConst45 * fRec22[0]) + (fConst59 * fRec22[1])) + (fConst45 * fRec22[2])));
			fRec21[0] = (fTemp96 - (fConst41 * ((fConst60 * fRec21[2]) + (fConst62 * fRec21[1]))));
			fRec20[0] = ((fConst41 * (((fConst43 * fRec21[0]) + (fConst63 * fRec21[1])) + (fConst43 * fRec21[2]))) - (fConst38 * ((fConst64 * fRec20[2]) + (fConst65 * fRec20[1]))));
			fRec19[0] = ((fConst38 * (((fConst40 * fRec20[0]) + (fConst66 * fRec20[1])) + (fConst40 * fRec20[2]))) - (fConst34 * ((fConst67 * fRec19[2]) + (fConst68 * fRec19[1]))));
			fRec18[0] = ((fSlow1 * fRec18[1]) + (fSlow2 * std::fabs((fConst34 * (((fConst37 * fRec19[0]) + (fConst69 * fRec19[1])) + (fConst37 * fRec19[2]))))));
			fVbargraph1 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec18[0])))));
			fRec31[0] = (fTemp96 - (fConst86 * ((fConst89 * fRec31[2]) + (fConst90 * fRec31[1]))));
			fRec30[0] = ((fConst86 * (((fConst88 * fRec31[0]) + (fConst91 * fRec31[1])) + (fConst88 * fRec31[2]))) - (fConst84 * ((fConst92 * fRec30[2]) + (fConst93 * fRec30[1]))));
			fRec29[0] = ((fConst84 * (((fConst85 * fRec30[0]) + (fConst94 * fRec30[1])) + (fConst85 * fRec30[2]))) - (fConst82 * ((fConst95 * fRec29[2]) + (fConst96 * fRec29[1]))));
			float fTemp97 = (fConst82 * (((fConst83 * fRec29[0]) + (fConst97 * fRec29[1])) + (fConst83 * fRec29[2])));
			fRec28[0] = (fTemp97 - (fConst79 * ((fConst98 * fRec28[2]) + (fConst100 * fRec28[1]))));
			fRec27[0] = ((fConst79 * (((fConst81 * fRec28[0]) + (fConst101 * fRec28[1])) + (fConst81 * fRec28[2]))) - (fConst76 * ((fConst102 * fRec27[2]) + (fConst103 * fRec27[1]))));
			fRec26[0] = ((fConst76 * (((fConst78 * fRec27[0]) + (fConst104 * fRec27[1])) + (fConst78 * fRec27[2]))) - (fConst72 * ((fConst105 * fRec26[2]) + (fConst106 * fRec26[1]))));
			fRec25[0] = ((fSlow1 * fRec25[1]) + (fSlow2 * std::fabs((fConst72 * (((fConst75 * fRec26[0]) + (fConst107 * fRec26[1])) + (fConst75 * fRec26[2]))))));
			fVbargraph2 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec25[0])))));
			fRec38[0] = (fTemp97 - (fConst124 * ((fConst127 * fRec38[2]) + (fConst128 * fRec38[1]))));
			fRec37[0] = ((fConst124 * (((fConst126 * fRec38[0]) + (fConst129 * fRec38[1])) + (fConst126 * fRec38[2]))) - (fConst122 * ((fConst130 * fRec37[2]) + (fConst131 * fRec37[1]))));
			fRec36[0] = ((fConst122 * (((fConst123 * fRec37[0]) + (fConst132 * fRec37[1])) + (fConst123 * fRec37[2]))) - (fConst120 * ((fConst133 * fRec36[2]) + (fConst134 * fRec36[1]))));
			float fTemp98 = (fConst120 * (((fConst121 * fRec36[0]) + (fConst135 * fRec36[1])) + (fConst121 * fRec36[2])));
			fRec35[0] = (fTemp98 - (fConst117 * ((fConst136 * fRec35[2]) + (fConst138 * fRec35[1]))));
			fRec34[0] = ((fConst117 * (((fConst119 * fRec35[0]) + (fConst139 * fRec35[1])) + (fConst119 * fRec35[2]))) - (fConst114 * ((fConst140 * fRec34[2]) + (fConst141 * fRec34[1]))));
			fRec33[0] = ((fConst114 * (((fConst116 * fRec34[0]) + (fConst142 * fRec34[1])) + (fConst116 * fRec34[2]))) - (fConst110 * ((fConst143 * fRec33[2]) + (fConst144 * fRec33[1]))));
			fRec32[0] = ((fSlow1 * fRec32[1]) + (fSlow2 * std::fabs((fConst110 * (((fConst113 * fRec33[0]) + (fConst145 * fRec33[1])) + (fConst113 * fRec33[2]))))));
			fVbargraph3 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec32[0])))));
			fRec45[0] = (fTemp98 - (fConst162 * ((fConst165 * fRec45[2]) + (fConst166 * fRec45[1]))));
			fRec44[0] = ((fConst162 * (((fConst164 * fRec45[0]) + (fConst167 * fRec45[1])) + (fConst164 * fRec45[2]))) - (fConst160 * ((fConst168 * fRec44[2]) + (fConst169 * fRec44[1]))));
			fRec43[0] = ((fConst160 * (((fConst161 * fRec44[0]) + (fConst170 * fRec44[1])) + (fConst161 * fRec44[2]))) - (fConst158 * ((fConst171 * fRec43[2]) + (fConst172 * fRec43[1]))));
			float fTemp99 = (fConst158 * (((fConst159 * fRec43[0]) + (fConst173 * fRec43[1])) + (fConst159 * fRec43[2])));
			fRec42[0] = (fTemp99 - (fConst155 * ((fConst174 * fRec42[2]) + (fConst176 * fRec42[1]))));
			fRec41[0] = ((fConst155 * (((fConst157 * fRec42[0]) + (fConst177 * fRec42[1])) + (fConst157 * fRec42[2]))) - (fConst152 * ((fConst178 * fRec41[2]) + (fConst179 * fRec41[1]))));
			fRec40[0] = ((fConst152 * (((fConst154 * fRec41[0]) + (fConst180 * fRec41[1])) + (fConst154 * fRec41[2]))) - (fConst148 * ((fConst181 * fRec40[2]) + (fConst182 * fRec40[1]))));
			fRec39[0] = ((fSlow1 * fRec39[1]) + (fSlow2 * std::fabs((fConst148 * (((fConst151 * fRec40[0]) + (fConst183 * fRec40[1])) + (fConst151 * fRec40[2]))))));
			fVbargraph4 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec39[0])))));
			fRec52[0] = (fTemp99 - (fConst200 * ((fConst203 * fRec52[2]) + (fConst204 * fRec52[1]))));
			fRec51[0] = ((fConst200 * (((fConst202 * fRec52[0]) + (fConst205 * fRec52[1])) + (fConst202 * fRec52[2]))) - (fConst198 * ((fConst206 * fRec51[2]) + (fConst207 * fRec51[1]))));
			fRec50[0] = ((fConst198 * (((fConst199 * fRec51[0]) + (fConst208 * fRec51[1])) + (fConst199 * fRec51[2]))) - (fConst196 * ((fConst209 * fRec50[2]) + (fConst210 * fRec50[1]))));
			float fTemp100 = (fConst196 * (((fConst197 * fRec50[0]) + (fConst211 * fRec50[1])) + (fConst197 * fRec50[2])));
			fRec49[0] = (fTemp100 - (fConst193 * ((fConst212 * fRec49[2]) + (fConst214 * fRec49[1]))));
			fRec48[0] = ((fConst193 * (((fConst195 * fRec49[0]) + (fConst215 * fRec49[1])) + (fConst195 * fRec49[2]))) - (fConst190 * ((fConst216 * fRec48[2]) + (fConst217 * fRec48[1]))));
			fRec47[0] = ((fConst190 * (((fConst192 * fRec48[0]) + (fConst218 * fRec48[1])) + (fConst192 * fRec48[2]))) - (fConst186 * ((fConst219 * fRec47[2]) + (fConst220 * fRec47[1]))));
			fRec46[0] = ((fSlow1 * fRec46[1]) + (fSlow2 * std::fabs((fConst186 * (((fConst189 * fRec47[0]) + (fConst221 * fRec47[1])) + (fConst189 * fRec47[2]))))));
			fVbargraph5 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec46[0])))));
			fRec59[0] = (fTemp100 - (fConst238 * ((fConst241 * fRec59[2]) + (fConst242 * fRec59[1]))));
			fRec58[0] = ((fConst238 * (((fConst240 * fRec59[0]) + (fConst243 * fRec59[1])) + (fConst240 * fRec59[2]))) - (fConst236 * ((fConst244 * fRec58[2]) + (fConst245 * fRec58[1]))));
			fRec57[0] = ((fConst236 * (((fConst237 * fRec58[0]) + (fConst246 * fRec58[1])) + (fConst237 * fRec58[2]))) - (fConst234 * ((fConst247 * fRec57[2]) + (fConst248 * fRec57[1]))));
			float fTemp101 = (fConst234 * (((fConst235 * fRec57[0]) + (fConst249 * fRec57[1])) + (fConst235 * fRec57[2])));
			fRec56[0] = (fTemp101 - (fConst231 * ((fConst250 * fRec56[2]) + (fConst252 * fRec56[1]))));
			fRec55[0] = ((fConst231 * (((fConst233 * fRec56[0]) + (fConst253 * fRec56[1])) + (fConst233 * fRec56[2]))) - (fConst228 * ((fConst254 * fRec55[2]) + (fConst255 * fRec55[1]))));
			fRec54[0] = ((fConst228 * (((fConst230 * fRec55[0]) + (fConst256 * fRec55[1])) + (fConst230 * fRec55[2]))) - (fConst224 * ((fConst257 * fRec54[2]) + (fConst258 * fRec54[1]))));
			fRec53[0] = ((fSlow1 * fRec53[1]) + (fSlow2 * std::fabs((fConst224 * (((fConst227 * fRec54[0]) + (fConst259 * fRec54[1])) + (fConst227 * fRec54[2]))))));
			fVbargraph6 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec53[0])))));
			fRec66[0] = (fTemp101 - (fConst276 * ((fConst279 * fRec66[2]) + (fConst280 * fRec66[1]))));
			fRec65[0] = ((fConst276 * (((fConst278 * fRec66[0]) + (fConst281 * fRec66[1])) + (fConst278 * fRec66[2]))) - (fConst274 * ((fConst282 * fRec65[2]) + (fConst283 * fRec65[1]))));
			fRec64[0] = ((fConst274 * (((fConst275 * fRec65[0]) + (fConst284 * fRec65[1])) + (fConst275 * fRec65[2]))) - (fConst272 * ((fConst285 * fRec64[2]) + (fConst286 * fRec64[1]))));
			float fTemp102 = (fConst272 * (((fConst273 * fRec64[0]) + (fConst287 * fRec64[1])) + (fConst273 * fRec64[2])));
			fRec63[0] = (fTemp102 - (fConst269 * ((fConst288 * fRec63[2]) + (fConst290 * fRec63[1]))));
			fRec62[0] = ((fConst269 * (((fConst271 * fRec63[0]) + (fConst291 * fRec63[1])) + (fConst271 * fRec63[2]))) - (fConst266 * ((fConst292 * fRec62[2]) + (fConst293 * fRec62[1]))));
			fRec61[0] = ((fConst266 * (((fConst268 * fRec62[0]) + (fConst294 * fRec62[1])) + (fConst268 * fRec62[2]))) - (fConst262 * ((fConst295 * fRec61[2]) + (fConst296 * fRec61[1]))));
			fRec60[0] = ((fSlow1 * fRec60[1]) + (fSlow2 * std::fabs((fConst262 * (((fConst265 * fRec61[0]) + (fConst297 * fRec61[1])) + (fConst265 * fRec61[2]))))));
			fVbargraph7 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec60[0])))));
			fRec73[0] = (fTemp102 - (fConst314 * ((fConst317 * fRec73[2]) + (fConst318 * fRec73[1]))));
			fRec72[0] = ((fConst314 * (((fConst316 * fRec73[0]) + (fConst319 * fRec73[1])) + (fConst316 * fRec73[2]))) - (fConst312 * ((fConst320 * fRec72[2]) + (fConst321 * fRec72[1]))));
			fRec71[0] = ((fConst312 * (((fConst313 * fRec72[0]) + (fConst322 * fRec72[1])) + (fConst313 * fRec72[2]))) - (fConst310 * ((fConst323 * fRec71[2]) + (fConst324 * fRec71[1]))));
			float fTemp103 = (fConst310 * (((fConst311 * fRec71[0]) + (fConst325 * fRec71[1])) + (fConst311 * fRec71[2])));
			fRec70[0] = (fTemp103 - (fConst307 * ((fConst326 * fRec70[2]) + (fConst328 * fRec70[1]))));
			fRec69[0] = ((fConst307 * (((fConst309 * fRec70[0]) + (fConst329 * fRec70[1])) + (fConst309 * fRec70[2]))) - (fConst304 * ((fConst330 * fRec69[2]) + (fConst331 * fRec69[1]))));
			fRec68[0] = ((fConst304 * (((fConst306 * fRec69[0]) + (fConst332 * fRec69[1])) + (fConst306 * fRec69[2]))) - (fConst300 * ((fConst333 * fRec68[2]) + (fConst334 * fRec68[1]))));
			fRec67[0] = ((fSlow1 * fRec67[1]) + (fSlow2 * std::fabs((fConst300 * (((fConst303 * fRec68[0]) + (fConst335 * fRec68[1])) + (fConst303 * fRec68[2]))))));
			fVbargraph8 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec67[0])))));
			fRec80[0] = (fTemp103 - (fConst352 * ((fConst355 * fRec80[2]) + (fConst356 * fRec80[1]))));
			fRec79[0] = ((fConst352 * (((fConst354 * fRec80[0]) + (fConst357 * fRec80[1])) + (fConst354 * fRec80[2]))) - (fConst350 * ((fConst358 * fRec79[2]) + (fConst359 * fRec79[1]))));
			fRec78[0] = ((fConst350 * (((fConst351 * fRec79[0]) + (fConst360 * fRec79[1])) + (fConst351 * fRec79[2]))) - (fConst348 * ((fConst361 * fRec78[2]) + (fConst362 * fRec78[1]))));
			float fTemp104 = (fConst348 * (((fConst349 * fRec78[0]) + (fConst363 * fRec78[1])) + (fConst349 * fRec78[2])));
			fRec77[0] = (fTemp104 - (fConst345 * ((fConst364 * fRec77[2]) + (fConst366 * fRec77[1]))));
			fRec76[0] = ((fConst345 * (((fConst347 * fRec77[0]) + (fConst367 * fRec77[1])) + (fConst347 * fRec77[2]))) - (fConst342 * ((fConst368 * fRec76[2]) + (fConst369 * fRec76[1]))));
			fRec75[0] = ((fConst342 * (((fConst344 * fRec76[0]) + (fConst370 * fRec76[1])) + (fConst344 * fRec76[2]))) - (fConst338 * ((fConst371 * fRec75[2]) + (fConst372 * fRec75[1]))));
			fRec74[0] = ((fSlow1 * fRec74[1]) + (fSlow2 * std::fabs((fConst338 * (((fConst341 * fRec75[0]) + (fConst373 * fRec75[1])) + (fConst341 * fRec75[2]))))));
			fVbargraph9 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec74[0])))));
			fRec87[0] = (fTemp104 - (fConst390 * ((fConst393 * fRec87[2]) + (fConst394 * fRec87[1]))));
			fRec86[0] = ((fConst390 * (((fConst392 * fRec87[0]) + (fConst395 * fRec87[1])) + (fConst392 * fRec87[2]))) - (fConst388 * ((fConst396 * fRec86[2]) + (fConst397 * fRec86[1]))));
			fRec85[0] = ((fConst388 * (((fConst389 * fRec86[0]) + (fConst398 * fRec86[1])) + (fConst389 * fRec86[2]))) - (fConst386 * ((fConst399 * fRec85[2]) + (fConst400 * fRec85[1]))));
			float fTemp105 = (fConst386 * (((fConst387 * fRec85[0]) + (fConst401 * fRec85[1])) + (fConst387 * fRec85[2])));
			fRec84[0] = (fTemp105 - (fConst383 * ((fConst402 * fRec84[2]) + (fConst404 * fRec84[1]))));
			fRec83[0] = ((fConst383 * (((fConst385 * fRec84[0]) + (fConst405 * fRec84[1])) + (fConst385 * fRec84[2]))) - (fConst380 * ((fConst406 * fRec83[2]) + (fConst407 * fRec83[1]))));
			fRec82[0] = ((fConst380 * (((fConst382 * fRec83[0]) + (fConst408 * fRec83[1])) + (fConst382 * fRec83[2]))) - (fConst376 * ((fConst409 * fRec82[2]) + (fConst410 * fRec82[1]))));
			fRec81[0] = ((fSlow1 * fRec81[1]) + (fSlow2 * std::fabs((fConst376 * (((fConst379 * fRec82[0]) + (fConst411 * fRec82[1])) + (fConst379 * fRec82[2]))))));
			fVbargraph10 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec81[0])))));
			fRec94[0] = (fTemp105 - (fConst428 * ((fConst431 * fRec94[2]) + (fConst432 * fRec94[1]))));
			fRec93[0] = ((fConst428 * (((fConst430 * fRec94[0]) + (fConst433 * fRec94[1])) + (fConst430 * fRec94[2]))) - (fConst426 * ((fConst434 * fRec93[2]) + (fConst435 * fRec93[1]))));
			fRec92[0] = ((fConst426 * (((fConst427 * fRec93[0]) + (fConst436 * fRec93[1])) + (fConst427 * fRec93[2]))) - (fConst424 * ((fConst437 * fRec92[2]) + (fConst438 * fRec92[1]))));
			float fTemp106 = (fConst424 * (((fConst425 * fRec92[0]) + (fConst439 * fRec92[1])) + (fConst425 * fRec92[2])));
			fRec91[0] = (fTemp106 - (fConst421 * ((fConst440 * fRec91[2]) + (fConst442 * fRec91[1]))));
			fRec90[0] = ((fConst421 * (((fConst423 * fRec91[0]) + (fConst443 * fRec91[1])) + (fConst423 * fRec91[2]))) - (fConst418 * ((fConst444 * fRec90[2]) + (fConst445 * fRec90[1]))));
			fRec89[0] = ((fConst418 * (((fConst420 * fRec90[0]) + (fConst446 * fRec90[1])) + (fConst420 * fRec90[2]))) - (fConst414 * ((fConst447 * fRec89[2]) + (fConst448 * fRec89[1]))));
			fRec88[0] = ((fSlow1 * fRec88[1]) + (fSlow2 * std::fabs((fConst414 * (((fConst417 * fRec89[0]) + (fConst449 * fRec89[1])) + (fConst417 * fRec89[2]))))));
			fVbargraph11 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec88[0])))));
			fRec101[0] = (fTemp106 - (fConst466 * ((fConst469 * fRec101[2]) + (fConst470 * fRec101[1]))));
			fRec100[0] = ((fConst466 * (((fConst468 * fRec101[0]) + (fConst471 * fRec101[1])) + (fConst468 * fRec101[2]))) - (fConst464 * ((fConst472 * fRec100[2]) + (fConst473 * fRec100[1]))));
			fRec99[0] = ((fConst464 * (((fConst465 * fRec100[0]) + (fConst474 * fRec100[1])) + (fConst465 * fRec100[2]))) - (fConst462 * ((fConst475 * fRec99[2]) + (fConst476 * fRec99[1]))));
			float fTemp107 = (fConst462 * (((fConst463 * fRec99[0]) + (fConst477 * fRec99[1])) + (fConst463 * fRec99[2])));
			fRec98[0] = (fTemp107 - (fConst459 * ((fConst478 * fRec98[2]) + (fConst480 * fRec98[1]))));
			fRec97[0] = ((fConst459 * (((fConst461 * fRec98[0]) + (fConst481 * fRec98[1])) + (fConst461 * fRec98[2]))) - (fConst456 * ((fConst482 * fRec97[2]) + (fConst483 * fRec97[1]))));
			fRec96[0] = ((fConst456 * (((fConst458 * fRec97[0]) + (fConst484 * fRec97[1])) + (fConst458 * fRec97[2]))) - (fConst452 * ((fConst485 * fRec96[2]) + (fConst486 * fRec96[1]))));
			fRec95[0] = ((fSlow1 * fRec95[1]) + (fSlow2 * std::fabs((fConst452 * (((fConst455 * fRec96[0]) + (fConst487 * fRec96[1])) + (fConst455 * fRec96[2]))))));
			fVbargraph12 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec95[0])))));
			fRec108[0] = (fTemp107 - (fConst504 * ((fConst507 * fRec108[2]) + (fConst508 * fRec108[1]))));
			fRec107[0] = ((fConst504 * (((fConst506 * fRec108[0]) + (fConst509 * fRec108[1])) + (fConst506 * fRec108[2]))) - (fConst502 * ((fConst510 * fRec107[2]) + (fConst511 * fRec107[1]))));
			fRec106[0] = ((fConst502 * (((fConst503 * fRec107[0]) + (fConst512 * fRec107[1])) + (fConst503 * fRec107[2]))) - (fConst500 * ((fConst513 * fRec106[2]) + (fConst514 * fRec106[1]))));
			float fTemp108 = (fConst500 * (((fConst501 * fRec106[0]) + (fConst515 * fRec106[1])) + (fConst501 * fRec106[2])));
			fRec105[0] = (fTemp108 - (fConst497 * ((fConst516 * fRec105[2]) + (fConst518 * fRec105[1]))));
			fRec104[0] = ((fConst497 * (((fConst499 * fRec105[0]) + (fConst519 * fRec105[1])) + (fConst499 * fRec105[2]))) - (fConst494 * ((fConst520 * fRec104[2]) + (fConst521 * fRec104[1]))));
			fRec103[0] = ((fConst494 * (((fConst496 * fRec104[0]) + (fConst522 * fRec104[1])) + (fConst496 * fRec104[2]))) - (fConst490 * ((fConst523 * fRec103[2]) + (fConst524 * fRec103[1]))));
			fRec102[0] = ((fSlow1 * fRec102[1]) + (fSlow2 * std::fabs((fConst490 * (((fConst493 * fRec103[0]) + (fConst525 * fRec103[1])) + (fConst493 * fRec103[2]))))));
			fVbargraph13 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec102[0])))));
			fRec112[0] = (fTemp108 - (fConst530 * ((fConst533 * fRec112[2]) + (fConst534 * fRec112[1]))));
			fRec111[0] = ((fConst530 * (((fConst532 * fRec112[0]) + (fConst535 * fRec112[1])) + (fConst532 * fRec112[2]))) - (fConst528 * ((fConst536 * fRec111[2]) + (fConst537 * fRec111[1]))));
			fRec110[0] = ((fConst528 * (((fConst529 * fRec111[0]) + (fConst538 * fRec111[1])) + (fConst529 * fRec111[2]))) - (fConst526 * ((fConst539 * fRec110[2]) + (fConst540 * fRec110[1]))));
			fRec109[0] = ((fSlow1 * fRec109[1]) + (fSlow2 * std::fabs((fConst526 * (((fConst527 * fRec110[0]) + (fConst541 * fRec110[1])) + (fConst527 * fRec110[2]))))));
			fVbargraph14 = FAUSTFLOAT((fSlow0 + (20.0f * std::log10(std::max<float>(1.00000001e-07f, fRec109[0])))));
			output0[i] = FAUSTFLOAT(fTemp95);
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				iVec0[j0] = iVec0[(j0 - 1)];
			}
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
			fVec1[1] = fVec1[0];
			fRec5[1] = fRec5[0];
			fVec2[1] = fVec2[0];
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fVec5[1] = fVec5[0];
			fVec6[1] = fVec6[0];
			fVec7[1] = fVec7[0];
			fVec8[1] = fVec8[0];
			fRec7[1] = fRec7[0];
			fVec9[1] = fVec9[0];
			fVec10[1] = fVec10[0];
			fVec11[1] = fVec11[0];
			fVec12[1] = fVec12[0];
			fVec13[1] = fVec13[0];
			fVec14[1] = fVec14[0];
			fVec15[1] = fVec15[0];
			fRec8[1] = fRec8[0];
			fVec16[1] = fVec16[0];
			fVec17[1] = fVec17[0];
			fVec18[1] = fVec18[0];
			fVec19[1] = fVec19[0];
			fVec20[1] = fVec20[0];
			fVec21[1] = fVec21[0];
			fVec22[1] = fVec22[0];
			fRec9[1] = fRec9[0];
			fVec23[1] = fVec23[0];
			IOTA = (IOTA + 1);
			fVec25[1] = fVec25[0];
			fRec10[1] = fRec10[0];
			fVec26[1] = fVec26[0];
			fVec28[1] = fVec28[0];
			fRec11[1] = fRec11[0];
			fVec29[1] = fVec29[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fVec31[1] = fVec31[0];
			fVec32[1] = fVec32[0];
			fRec15[1] = fRec15[0];
			fVec34[1] = fVec34[0];
			fVec35[1] = fVec35[0];
			fVec37[1] = fVec37[0];
			fVec38[1] = fVec38[0];
			iRec17[1] = iRec17[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec16[j1] = fRec16[(j1 - 1)];
			}
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[1] = fRec53[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec60[1] = fRec60[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[1] = fRec67[0];
			fRec80[2] = fRec80[1];
			fRec80[1] = fRec80[0];
			fRec79[2] = fRec79[1];
			fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec74[1] = fRec74[0];
			fRec87[2] = fRec87[1];
			fRec87[1] = fRec87[0];
			fRec86[2] = fRec86[1];
			fRec86[1] = fRec86[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec84[2] = fRec84[1];
			fRec84[1] = fRec84[0];
			fRec83[2] = fRec83[1];
			fRec83[1] = fRec83[0];
			fRec82[2] = fRec82[1];
			fRec82[1] = fRec82[0];
			fRec81[1] = fRec81[0];
			fRec94[2] = fRec94[1];
			fRec94[1] = fRec94[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec92[2] = fRec92[1];
			fRec92[1] = fRec92[0];
			fRec91[2] = fRec91[1];
			fRec91[1] = fRec91[0];
			fRec90[2] = fRec90[1];
			fRec90[1] = fRec90[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec88[1] = fRec88[0];
			fRec101[2] = fRec101[1];
			fRec101[1] = fRec101[0];
			fRec100[2] = fRec100[1];
			fRec100[1] = fRec100[0];
			fRec99[2] = fRec99[1];
			fRec99[1] = fRec99[0];
			fRec98[2] = fRec98[1];
			fRec98[1] = fRec98[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec95[1] = fRec95[0];
			fRec108[2] = fRec108[1];
			fRec108[1] = fRec108[0];
			fRec107[2] = fRec107[1];
			fRec107[1] = fRec107[0];
			fRec106[2] = fRec106[1];
			fRec106[1] = fRec106[0];
			fRec105[2] = fRec105[1];
			fRec105[1] = fRec105[0];
			fRec104[2] = fRec104[1];
			fRec104[1] = fRec104[0];
			fRec103[2] = fRec103[1];
			fRec103[1] = fRec103[0];
			fRec102[1] = fRec102[0];
			fRec112[2] = fRec112[1];
			fRec112[1] = fRec112[0];
			fRec111[2] = fRec111[1];
			fRec111[1] = fRec111[0];
			fRec110[2] = fRec110[1];
			fRec110[1] = fRec110[0];
			fRec109[1] = fRec109[0];
		}
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

//#define A1S_BOARD true                  //uncomment for Ai-thinker A1S board

#define MULT_S32 2147483647
#define DIV_S32 4.6566129e-10
#define clip(sample) std::max(-MULT_S32, std::min(MULT_S32, ((int32_t)(sample * MULT_S32))));

lab::lab(int sample_rate, int buffer_size)
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

lab::~lab()
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

bool lab::start()
{
    xTaskCreate(audioTaskHandler, "Faust DSP Task", 1024, (void*)this, 5, &fHandle);
    return true;
}

void lab::stop()
{
    if (fHandle != NULL) {
        vTaskDelete(fHandle);
        fHandle = NULL;
    }
}

void lab::setParamValue(const std::string& path, float value)
{
    fUI->setParamValue(path, value);
}

void lab::configureI2S(int sample_rate, int buffer_size, i2s_pin_config_t pin_config)
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

void lab::audioTask()
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

void lab::audioTaskHandler(void* arg)
{
    lab* audio = (lab*)arg;
    audio->audioTask();
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

#endif

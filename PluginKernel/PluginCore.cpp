// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.cpp
//
/**
    \file   plugincore.cpp
    \author Will Pirkle
    \date   17-September-2018
    \brief  Implementation file for PluginCore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#include "plugincore.h"
#include "plugindescription.h"

/**
\brief PluginCore constructor is launching pad for object initialization

Operations:
- initialize the plugin description (strings, codes, numbers, see initPluginDescriptors())
- setup the plugin's audio I/O channel support
- create the PluginParameter objects that represent the plugin parameters (see FX book if needed)
- create the presets
*/
PluginCore::PluginCore()
{
    // --- describe the plugin; call the helper to init the static parts you setup in plugindescription.h
    initPluginDescriptors();

    // --- default I/O combinations
	// --- for FX plugins
	if (getPluginType() == kFXPlugin)
	{
		addSupportedIOCombination({ kCFMono, kCFMono });
		addSupportedIOCombination({ kCFMono, kCFStereo });
		addSupportedIOCombination({ kCFStereo, kCFStereo });
	}
	else // --- synth plugins have no input, only output
	{
		addSupportedIOCombination({ kCFNone, kCFMono });
		addSupportedIOCombination({ kCFNone, kCFStereo });
	}

	// --- for sidechaining, we support mono and stereo inputs; auxOutputs reserved for future use
	addSupportedAuxIOCombination({ kCFMono, kCFNone });
	addSupportedAuxIOCombination({ kCFStereo, kCFNone });

	// --- create the parameters
    initPluginParameters();

    // --- create the presets
    initPluginPresets();
}

/**
\brief create all of your plugin parameters here

\return true if parameters were created, false if they already existed
*/
bool PluginCore::initPluginParameters()
{
	if (pluginParameterMap.size() > 0)
		return false;

    // --- Add your plugin parameter instantiation code bewtween these hex codes
	// **--0xDEA7--**


	// --- Declaration of Plugin Parameter Objects 
	PluginParameter* piParam = nullptr;

	// --- continuous control: Dry/Wet
	piParam = new PluginParameter(controlID::wet_mix, "Dry/Wet", "%", controlVariableType::kDouble, 0.000000, 100.000000, 50.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&wet_mix, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Decay
	piParam = new PluginParameter(controlID::decay, "Decay", "", controlVariableType::kDouble, 0.000000, 0.900000, 0.300000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&decay, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Damping
	piParam = new PluginParameter(controlID::damping, "Damping", "Hz", controlVariableType::kDouble, 2000.000000, 20000.000000, 10000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&damping, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Low Pass
	piParam = new PluginParameter(controlID::lowpass_freq, "Low Pass", "Hz", controlVariableType::kDouble, 1000.000000, 20000.000000, 10000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&lowpass_freq, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Mod Rate
	piParam = new PluginParameter(controlID::mod_rate, "Mod Rate", "Units", controlVariableType::kDouble, 0.100000, 100.000000, 0.100000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&mod_rate, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Mod Depth
	piParam = new PluginParameter(controlID::mod_dpeth, "Mod Depth", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.100000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&mod_dpeth, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Pre Delay
	piParam = new PluginParameter(controlID::predelay_time, "Pre Delay", "ms", controlVariableType::kDouble, 0.000000, 100.000000, 15.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(true);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&predelay_time, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- Aux Attributes
	AuxParameterAttribute auxAttribute;

	// --- RAFX GUI attributes
	// --- controlID::wet_mix
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::wet_mix, auxAttribute);

	// --- controlID::decay
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::decay, auxAttribute);

	// --- controlID::damping
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::damping, auxAttribute);

	// --- controlID::lowpass_freq
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::lowpass_freq, auxAttribute);

	// --- controlID::mod_rate
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::mod_rate, auxAttribute);

	// --- controlID::mod_dpeth
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::mod_dpeth, auxAttribute);

	// --- controlID::predelay_time
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::predelay_time, auxAttribute);


	// **--0xEDA5--**
   
    // --- BONUS Parameter
    // --- SCALE_GUI_SIZE
    PluginParameter* piParamBonus = new PluginParameter(SCALE_GUI_SIZE, "Scale GUI", "tiny,small,medium,normal,large,giant", "normal");
    addPluginParameter(piParamBonus);

	// --- create the super fast access array
	initPluginParameterArray();

    return true;
}

/**
\brief initialize object for a new run of audio; called just before audio streams

Operation:
- store sample rate and bit depth on audioProcDescriptor - this information is globally available to all core functions
- reset your member objects here

\param resetInfo structure of information about current audio format

\return true if operation succeeds, false otherwise
*/
bool PluginCore::reset(ResetInfo& resetInfo)
{
    // --- save for audio processing
    audioProcDescriptor.sampleRate = resetInfo.sampleRate;
    audioProcDescriptor.bitDepth = resetInfo.bitDepth;
	apf1.reset(resetInfo.sampleRate);
	apf2.reset(resetInfo.sampleRate);
	apf3.reset(resetInfo.sampleRate);
	apf4.reset(resetInfo.sampleRate);
	apf5.reset(resetInfo.sampleRate);
	apf6.reset(resetInfo.sampleRate);
	apf1.createDelayBuffer(resetInfo.sampleRate, 211);
	apf2.createDelayBuffer(resetInfo.sampleRate, 159);
	apf3.createDelayBuffer(resetInfo.sampleRate, 562);
	apf4.createDelayBuffer(resetInfo.sampleRate, 411);
	apf5.createDelayBuffer(resetInfo.sampleRate, 3932);
	apf6.createDelayBuffer(resetInfo.sampleRate, 2665);
	DelayAPFParameters apf1p = apf1.getParameters();
	apf1p.apf_g = 0.75;
	apf1p.delayTime_mSec = 210/44.1;
	apf1.setParameters(apf1p);
	DelayAPFParameters apf2p = apf2.getParameters();
	apf2p.apf_g = 0.75;
	apf2p.delayTime_mSec = 158/44.1;
	apf2.setParameters(apf2p);
	DelayAPFParameters apf3p = apf3.getParameters();
	apf3p.apf_g = 0.625;
	apf3p.delayTime_mSec = 561/44.1;
	apf3.setParameters(apf3p);
	DelayAPFParameters apf4p = apf4.getParameters();
	apf4p.apf_g = 0.625;
	apf4p.delayTime_mSec = 410/44.1;
	apf4.setParameters(apf4p);
	DelayAPFParameters apf5p = apf5.getParameters();
	apf5p.apf_g = 0.5;
	apf5p.delayTime_mSec = 3931/44.1;
	apf5.setParameters(apf5p);
	DelayAPFParameters apf6p = apf6.getParameters();
	apf6p.apf_g = 0.5;
	apf5p.delayTime_mSec = 2664/44.1;
	apf6.setParameters(apf6p);

	delay1.reset(resetInfo.sampleRate);
	delay2.reset(resetInfo.sampleRate);
	delay3.reset(resetInfo.sampleRate);
	delay4.reset(resetInfo.sampleRate);
	delay1.createDelayBuffer(resetInfo.sampleRate, 6241);
	delay2.createDelayBuffer(resetInfo.sampleRate, 6590);
	delay3.createDelayBuffer(resetInfo.sampleRate, 4641);
	delay4.createDelayBuffer(resetInfo.sampleRate, 5505);
	preDelay.reset(resetInfo.sampleRate);
	preDelay.createDelayBuffer(resetInfo.sampleRate, 1024);

	modAPF1.reset(resetInfo.sampleRate);
	modAPF2.reset(resetInfo.sampleRate);
	modAPF1.createDelayBuffer(resetInfo.sampleRate, 1363);
	modAPF2.createDelayBuffer(resetInfo.sampleRate, 1105);
	DelayAPFParameters mod1p = modAPF1.getParameters();
	mod1p.lfoMaxModulation_mSec = 100;
	mod1p.enableLFO = true;
	mod1p.apf_g = 0.7;
	mod1p.lfoRate_Hz = 0.1;
	mod1p.lfoDepth = 0.1;
	mod1p.delayTime_mSec = 1343/44.1;
	modAPF1.setParameters(mod1p);
	DelayAPFParameters mod2p = modAPF2.getParameters();
	mod2p.lfoMaxModulation_mSec = 100;
	mod2p.enableLFO = true;  
	mod2p.apf_g = 0.7;
	mod2p.lfoRate_Hz = 0.1;
	mod2p.lfoDepth = 0.1;
	mod2p.delayTime_mSec = 995/44.1;
	modAPF2.setParameters(mod2p);
	for (int i = 0; i < 3; i++) {
		LPF[i].reset(resetInfo.sampleRate);
		AudioFilterParameters LPFparams = LPF[i].getParameters();
		LPFparams.algorithm = filterAlgorithm::kLPF1;
		LPFparams.fc = 10000;
		LPF[i].setParameters(LPFparams);
	}
	
    // --- other reset inits
    return PluginBase::reset(resetInfo);
}

void PluginCore::UpdateParameters() {
	G = decay;
	for (int i = 1; i < 3; i++) {
		AudioFilterParameters lpfP = LPF[i].getParameters();
		lpfP.fc = damping;
		LPF[i].setParameters(lpfP);
	}
	AudioFilterParameters lpfParams = LPF[0].getParameters();
	lpfParams.fc = lowpass_freq;
	LPF[0].setParameters(lpfParams);

	DelayAPFParameters mod1Params = modAPF1.getParameters();
	mod1Params.lfoDepth = mod_dpeth;
	mod1Params.lfoRate_Hz = mod_rate;
	modAPF1.setParameters(mod1Params);

	DelayAPFParameters mod2Params = modAPF2.getParameters();
	mod1Params.lfoDepth = mod_dpeth;
	mod1Params.lfoRate_Hz = mod_rate;
	modAPF2.setParameters(mod2Params);

	SimpleDelayParameters preDelayParams = preDelay.getParameters();
	preDelayParams.delayTime_mSec = predelay_time;
	preDelay.setParameters(preDelayParams);
}

/**
\brief one-time initialize function called after object creation and before the first reset( ) call

Operation:
- saves structure for the plugin to use; you can also load WAV files or state information here
*/
bool PluginCore::initialize(PluginInfo& pluginInfo)
{
	// --- add one-time init stuff here

	return true;
}

/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- syncInBoundVariables when preProcessAudioBuffers is called, it is *guaranteed* that all GUI control change information
  has been applied to plugin parameters; this binds parameter changes to your underlying variables
- NOTE: postUpdatePluginParameter( ) will be called for all bound variables that are acutally updated; if you need to process
  them individually, do so in that function
- use this function to bulk-transfer the bound variable data into your plugin's member object variables

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::preProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
    // --- sync internal variables to GUI parameters; you can also do this manually if you don't
    //     want to use the auto-variable-binding
    syncInBoundVariables();

    return true;
}

/**
\brief frame-processing method

Operation:
- decode the plugin type - for synth plugins, fill in the rendering code; for FX plugins, delete the if(synth) portion and add your processing code
- note that MIDI events are fired for each sample interval so that MIDI is tightly sunk with audio
- doSampleAccurateParameterUpdates will perform per-sample interval smoothing

\param processFrameInfo structure of information about *frame* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processAudioFrame(ProcessFrameInfo& processFrameInfo)
{
    // --- fire any MIDI events for this sample interval
    processFrameInfo.midiEventQueue->fireMidiEvents(processFrameInfo.currentFrame);

	// --- do per-frame updates; VST automation and parameter smoothing
	doSampleAccurateParameterUpdates();
	UpdateParameters();
    // --- decode the channelIOConfiguration and process accordingly
    //
	// --- Synth Plugin:
	// --- Synth Plugin --- remove for FX plugins
	if (getPluginType() == kSynthPlugin)
	{
		// --- output silence: change this with your signal render code
		processFrameInfo.audioOutputFrame[0] = 0.0;
		if (processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
			processFrameInfo.audioOutputFrame[1] = 0.0;

		return true;	/// processed
	}

    // --- FX Plugin:
    if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFMono)
    {
		// --- pass through code: change this with your signal processing
        processFrameInfo.audioOutputFrame[0] = processFrameInfo.audioInputFrame[0];

        return true; /// processed
    }

    // --- Mono-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing
		double L = processFrameInfo.audioInputFrame[0];
		//double R = processFrameInfo.audioInputFrame[1];
		//double inputSum = (L + R) * 0.5;
		double pre = preDelay.processAudioSample(L);
		double lp1 = LPF[0].processAudioSample(pre);
		double AP1 = apf1.processAudioSample(lp1);
		double AP2 = apf2.processAudioSample(AP1);
		double AP3 = apf3.processAudioSample(AP2);
		double AP4 = apf4.processAudioSample(AP3);
		x1 = AP4;
		double sumX1X2 = x1 + x3;
		double mod1 = modAPF1.processAudioSample(sumX1X2);
		double del1 = delay1.processAudioSample(mod1);
		double LP2 = LPF[1].processAudioSample(del1);
		double AP5 = apf5.processAudioSample(LP2);
		double del2 = delay2.processAudioSample(AP5);
		x2 = del2;
		x2 *= G;
		double mod2 = modAPF2.processAudioSample(x2);
		double del3 = delay3.processAudioSample(mod2);
		double LP3 = LPF[2].processAudioSample(del3);
		double AP6 = apf6.processAudioSample(LP3);
		double del4 = delay4.processAudioSample(AP6);
		x3 = del4;
		x3 *= G;
		double a1 = delay1.readDelayAtTime_mSec(394/44.1);
		double a2 = delay1.readDelayAtTime_mSec(4401/44.1);
		double a3 = delay1.readDelayAtTime_mSec(3124/44.1);
		double b1 = apf5.readDelay(2831/44.1);
		double b2 = apf5.readDelay(496/44.1);
		double c1 = delay2.readDelayAtTime_mSec(2954/44.1);
		double c2 = delay2.readDelayAtTime_mSec(179/44.1);
		double d1 = delay3.readDelayAtTime_mSec(2945/44.1);
		double d2 = delay3.readDelayAtTime_mSec(522/44.1);
		double d3 = delay3.readDelayAtTime_mSec(5368/44.1);
		double e1 = apf6.readDelay(277/44.1);
		double e2 = apf6.readDelay(1817/44.1);
		double f1 = delay4.readDelayAtTime_mSec(1578/44.1);
		double f2 = delay4.readDelayAtTime_mSec(3956/44.1);

		double yL = 0;
		double yR = 0;
		yL = a1 + a2 - b1 + c1 - d1 - e1 - f1;
		yR = d2 + d3 - e2 + f2 - a3 - b2 - c2;
		double wet = (wet_mix / 100);
		double dry = (1 - wet_mix / 100);
        processFrameInfo.audioOutputFrame[0] = yL * wet + L * dry;//processFrameInfo.audioInputFrame[0];
        processFrameInfo.audioOutputFrame[1] = yR * wet + L * dry;//processFrameInfo.audioInputFrame[0];

        return true; /// processed
    }

    // --- Stereo-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFStereo &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		//double sampleRate = getSampleRate();
		// --- pass through code: change this with your signal processing
		double L = processFrameInfo.audioInputFrame[0];
		double R = processFrameInfo.audioInputFrame[1];
		double inputSum = (L + R) * 0.5;
		double pre = preDelay.processAudioSample(inputSum);
		double lp1 = LPF[0].processAudioSample(pre);
		double AP1 = apf1.processAudioSample(lp1);
		double AP2 = apf2.processAudioSample(AP1);
		double AP3 = apf3.processAudioSample(AP2);
		double AP4 = apf4.processAudioSample(AP3);
		x1 = AP4;
		double sumX1X2 = x1 + x3;
		double mod1 = modAPF1.processAudioSample(sumX1X2);
		double del1 = delay1.processAudioSample(mod1);
		double LP2 = LPF[1].processAudioSample(del1);
		double AP5 = apf5.processAudioSample(LP2);
		double del2 = delay2.processAudioSample(AP5);
		x2 = del2;
		x2 *= G;
		double mod2 = modAPF2.processAudioSample(x2);
		double del3 = delay3.processAudioSample(mod2);
		double LP3 = LPF[2].processAudioSample(del3);
		double AP6 = apf6.processAudioSample(LP3);
		double del4 = delay4.processAudioSample(AP6);
		x3 = del4;
		x3 *= G;
		double a1 = delay1.readDelayAtTime_mSec(394/44.1);
		double a2 = delay1.readDelayAtTime_mSec(4401/44.1);
		double a3 = delay1.readDelayAtTime_mSec(3124/44.1);
		double b1 = apf5.readDelay(2831/44.1);
		double b2 = apf5.readDelay(496/44.1);
		double c1 = delay2.readDelayAtTime_mSec(2954/44.1);
		double c2 = delay2.readDelayAtTime_mSec(179/44.1);
		double d1 = delay3.readDelayAtTime_mSec(2945/44.1);
		double d2 = delay3.readDelayAtTime_mSec(522/44.1);
		double d3 = delay3.readDelayAtTime_mSec(5368/44.1);
		double e1 = apf6.readDelay(277/44.1);
		double e2 = apf6.readDelay(1817/44.1);
		double f1 = delay4.readDelayAtTime_mSec(1578/44.1);
		double f2 = delay4.readDelayAtTime_mSec(3956/44.1);

		double yL = 0;
		double yR = 0;
		yL = a1 + a2 - b1 + c1 - d1 - e1 - f1;
		yR = d2 + d3 - e2 + f2 - a3 - b2 - c2;
		double wet = (wet_mix / 100);
		double dry = (1 - wet_mix / 100);
		processFrameInfo.audioOutputFrame[0] = yL *wet + L *dry;//processFrameInfo.audioInputFrame[0];
		processFrameInfo.audioOutputFrame[1] = yR *wet + R *dry;//processFrameInfo.audioInputFrame[1];

        return true; /// processed
    }

    return false; /// NOT processed
}


/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- updateOutBoundVariables sends metering data to the GUI meters

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
	// --- update outbound variables; currently this is meter data only, but could be extended
	//     in the future
	updateOutBoundVariables();

    return true;
}

/**
\brief update the PluginParameter's value based on GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- use base class helper
    setPIParamValue(controlID, controlValue);

    // --- do any post-processing
    postUpdatePluginParameter(controlID, controlValue, paramInfo);

    return true; /// handled
}

/**
\brief update the PluginParameter's value based on *normlaized* GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param normalizedValue the new control value in normalized form
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo)
{
	// --- use base class helper, returns actual value
	double controlValue = setPIParamValueNormalized(controlID, normalizedValue, paramInfo.applyTaper);

	// --- do any post-processing
	postUpdatePluginParameter(controlID, controlValue, paramInfo);

	return true; /// handled
}

/**
\brief perform any operations after the plugin parameter has been updated; this is one paradigm for
	   transferring control information into vital plugin variables or member objects. If you use this
	   method you can decode the control ID and then do any cooking that is needed. NOTE: do not
	   overwrite bound variables here - this is ONLY for any extra cooking that is required to convert
	   the GUI data to meaninful coefficients or other specific modifiers.

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- now do any post update cooking; be careful with VST Sample Accurate automation
    //     If enabled, then make sure the cooking functions are short and efficient otherwise disable it
    //     for the Parameter involved
    /*switch(controlID)
    {
        case 0:
        {
            return true;    /// handled
        }

        default:
            return false;   /// not handled
    }*/

    return false;
}

/**
\brief has nothing to do with actual variable or updated variable (binding)

CAUTION:
- DO NOT update underlying variables here - this is only for sending GUI updates or letting you
  know that a parameter was changed; it should not change the state of your plugin.

WARNING:
- THIS IS NOT THE PREFERRED WAY TO LINK OR COMBINE CONTROLS TOGETHER. THE PROPER METHOD IS
  TO USE A CUSTOM SUB-CONTROLLER THAT IS PART OF THE GUI OBJECT AND CODE.
  SEE http://www.willpirkle.com for more information

\param controlID the control ID value of the parameter being updated
\param actualValue the new control value

\return true if operation succeeds, false otherwise
*/
bool PluginCore::guiParameterChanged(int32_t controlID, double actualValue)
{
	/*
	switch (controlID)
	{
		case controlID::<your control here>
		{

			return true; // handled
		}

		default:
			break;
	}*/

	return false; /// not handled
}

/**
\brief For Custom View and Custom Sub-Controller Operations

NOTES:
- this is for advanced users only to implement custom view and custom sub-controllers
- see the SDK for examples of use

\param messageInfo a structure containing information about the incoming message

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMessage(MessageInfo& messageInfo)
{
	// --- decode message
	switch (messageInfo.message)
	{
		// --- add customization appearance here
	case PLUGINGUI_DIDOPEN:
	{
		return false;
	}

	// --- NULL pointers so that we don't accidentally use them
	case PLUGINGUI_WILLCLOSE:
	{
		return false;
	}

	// --- update view; this will only be called if the GUI is actually open
	case PLUGINGUI_TIMERPING:
	{
		return false;
	}

	// --- register the custom view, grab the ICustomView interface
	case PLUGINGUI_REGISTER_CUSTOMVIEW:
	{

		return false;
	}

	case PLUGINGUI_REGISTER_SUBCONTROLLER:
	case PLUGINGUI_QUERY_HASUSERCUSTOM:
	case PLUGINGUI_USER_CUSTOMOPEN:
	case PLUGINGUI_USER_CUSTOMCLOSE:
	case PLUGINGUI_EXTERNAL_SET_NORMVALUE:
	case PLUGINGUI_EXTERNAL_SET_ACTUALVALUE:
	{

		return false;
	}

	default:
		break;
	}

	return false; /// not handled
}


/**
\brief process a MIDI event

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param event a structure containing the MIDI event data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMIDIEvent(midiEvent& event)
{
	return true;
}

/**
\brief (for future use)

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param vectorJoysickData a structure containing joystick data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData)
{
	return true;
}

/**
\brief use this method to add new presets to the list

NOTES:
- see the SDK for examples of use
- for non RackAFX users that have large paramter counts, there is a secret GUI control you
  can enable to write C++ code into text files, one per preset. See the SDK or http://www.willpirkle.com for details

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginPresets()
{
	// **--0xFF7A--**

	// --- Plugin Presets 
	int index = 0;
	PresetInfo* preset = nullptr;

	// --- Preset: Factory Preset
	preset = new PresetInfo(index++, "Factory Preset");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::wet_mix, 50.000000);
	setPresetParameter(preset->presetParameters, controlID::decay, 0.300000);
	setPresetParameter(preset->presetParameters, controlID::damping, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::lowpass_freq, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::mod_rate, 0.100000);
	setPresetParameter(preset->presetParameters, controlID::mod_dpeth, 0.100000);
	setPresetParameter(preset->presetParameters, controlID::predelay_time, 15.000001);
	addPreset(preset);


	// **--0xA7FF--**

    return true;
}

/**
\brief setup the plugin description strings, flags and codes; this is ordinarily done through the ASPiKreator or CMake

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginDescriptors()
{
    pluginDescriptor.pluginName = PluginCore::getPluginName();
    pluginDescriptor.shortPluginName = PluginCore::getShortPluginName();
    pluginDescriptor.vendorName = PluginCore::getVendorName();
    pluginDescriptor.pluginTypeCode = PluginCore::getPluginType();

	// --- describe the plugin attributes; set according to your needs
	pluginDescriptor.hasSidechain = kWantSidechain;
	pluginDescriptor.latencyInSamples = kLatencyInSamples;
	pluginDescriptor.tailTimeInMSec = kTailTimeMsec;
	pluginDescriptor.infiniteTailVST3 = kVSTInfiniteTail;

    // --- AAX
    apiSpecificInfo.aaxManufacturerID = kManufacturerID;
    apiSpecificInfo.aaxProductID = kAAXProductID;
    apiSpecificInfo.aaxBundleID = kAAXBundleID;  /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.aaxEffectID = "aaxDeveloper.";
    apiSpecificInfo.aaxEffectID.append(PluginCore::getPluginName());
    apiSpecificInfo.aaxPluginCategoryCode = kAAXCategory;

    // --- AU
    apiSpecificInfo.auBundleID = kAUBundleID;
	apiSpecificInfo.auBundleName = kAUBundleName;   /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.auBundleName = kAUBundleName;

    // --- VST3
    apiSpecificInfo.vst3FUID = PluginCore::getVSTFUID(); // OLE string format
    apiSpecificInfo.vst3BundleID = kVST3BundleID;/* MacOS only: this MUST match the bundle identifier in your info.plist file */
	apiSpecificInfo.enableVST3SampleAccurateAutomation = kVSTSAA;
	apiSpecificInfo.vst3SampleAccurateGranularity = kVST3SAAGranularity;

    // --- AU and AAX
    apiSpecificInfo.fourCharCode = PluginCore::getFourCharCode();

    return true;
}

// --- static functions required for VST3/AU only --------------------------------------------- //
const char* PluginCore::getPluginBundleName() { return kAUBundleName; }
const char* PluginCore::getPluginName(){ return kPluginName; }
const char* PluginCore::getShortPluginName(){ return kShortPluginName; }
const char* PluginCore::getVendorName(){ return kVendorName; }
const char* PluginCore::getVendorURL(){ return kVendorURL; }
const char* PluginCore::getVendorEmail(){ return kVendorEmail; }
const char* PluginCore::getAUCocoaViewFactoryName(){ return AU_COCOA_VIEWFACTORY_STRING; }
pluginType PluginCore::getPluginType(){ return kPluginType; }
const char* PluginCore::getVSTFUID(){ return kVSTFUID; }
int32_t PluginCore::getFourCharCode(){ return kFourCharCode; }

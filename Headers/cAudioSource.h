// Copyright (c) 2008-2010 Raynaldo (Wildicv) Rivera, Joshua (Dark_Kilauea) Jones
// This file is part of the "cAudio Engine"
// For conditions of distribution and use, see copyright notice in cAudio.h

#ifndef CAUDIOSOURCE_H_INCLUDED
#define CAUDIOSOURCE_H_INCLUDED
#include <list>
#include <string>
#include <vector>
#include <AL/al.h>
#include <AL/alc.h>

#include "../include/IAudioSource.h"
#include "../include/cVector3.h"
#include "../Headers/cMutex.h"
#include "../include/ILogger.h"
#include "../Headers/cEFXFunctions.h"

namespace cAudio
{

    class cAudioSource : public IAudioSource
    {
    public:

		enum Events{
			ON_INIT,
			ON_UPDATE,
			ON_RELEASE,
			ON_PLAY,
			ON_PAUSE,
			ON_STOP,
		};

#ifdef CAUDIO_EFX_ENABLED
		cAudioSource(IAudioDecoder* decoder, ALCcontext* context, cEFXFunctions* oALFunctions);
#else
		cAudioSource(IAudioDecoder* decoder, ALCcontext* context);
#endif
		~cAudioSource();

		//! Plays the source with the default or last set values
		virtual bool play();
		//! Plays the source in 2D mode
		virtual bool play2d(const bool& toLoop = false);
		//! Plays the source in 3D mode
		virtual bool play3d(const cVector3& position, const float& soundstr = 1.0 , const bool& toLoop = false);
		
		//! Pauses playback of the sound source 
		virtual void pause();
		//! Stops playback of the sound source       
		virtual void stop();
		//! Controls whether the source should loop or not
		virtual void loop(const bool& toLoop);
		//! Seeks through the audio stream to a specific spot
		/** Note: May not be supported by all codecs
		\param seconds: Number of seconds to seek
		\param relative: Whether to seek from the current position or the start of the stream
		\return True on success, False if the codec does not support seeking. */
		virtual bool seek(const float& seconds, bool relative = false);

		//! Normally called every frame by the audio manager to update the internal buffers
		//! Note: For internal use only.
		virtual bool update();
		//! Releases all resources used by the audio source, normally used to clean up before deletion
		//! Note: For internal use only.
		virtual void release();

		//! Returns if the source is ready to be used
		virtual const bool isValid() const;
		//! Returns if the source is playing
		virtual const bool isPlaying() const;
		//! Returns if the source is paused
		virtual const bool isPaused() const;
		//! Returns if the source is stopped
		virtual const bool isStopped() const;
		//! Returns if the source is looping
		virtual const bool isLooping() const;

		//! Sets the position of the source in 3D space       
		virtual void setPosition(const cVector3& position);
		//! Sets the current velocity of the source for doppler effects
		virtual void setVelocity(const cVector3& velocity);
		//! Sets the direction the source is facing
		virtual void setDirection(const cVector3& direction);

		//! Sets the factor used in attenuating the source over distance
		//! Larger values make it attenuate faster, smaller values make the source carry better
		//! Range: 0.0f to +inf (Default: 1.0f)
		virtual void setRolloffFactor(const float& rolloff);
		//! Sets how well the source carries over distance
		//! Same as setRolloffFactor(1.0f/soundstrength)
		//! Range: 0.0f to +inf (Default: 1.0f)
		virtual void setStrength(const float& soundstrength);
		//! Sets the distance from the source where attenuation will begin
		//! Range: 0.0f to +inf
		virtual void setMinDistance(const float& minDistance);
		//! Sets the distance from the source where attenuation will stop
		//! Range: 0.0f to +inf
		virtual void setMaxDistance(const float& maxDistance);

		//! Sets the pitch of the source
		virtual void setPitch(const float& pitch);
		//! Sets the source volume before attenuation and other effects
		//! Range: 0.0f to +inf (Default: 1.0f)
		virtual void setVolume(const float& volume);
		//! Sets the minimum volume that the source can be attenuated to
		//! Range: 0.0f to +inf (Default: 0.0f)
		virtual void setMinVolume(const float& minVolume);
		//! Sets the maximum volume that the source can achieve
		//! Range: 0.0f to +inf (Default: 1.0f)
		virtual void setMaxVolume(const float& maxVolume);

		//! Sets the angle of the inner sound cone of the source
		//! Note: This causes the sound to be loudest only if the listener is inside this cone
		//! Range: 0.0f to 360.0f (Default: 360.0f)
		virtual void setInnerConeAngle(const float& innerAngle);
		//! Sets the angle of the outer sound cone of the source
		//! Note: If the listener is outside of this cone, the sound cannot be heard.  Between the inner cone angle and this angle, the sound volume will fall off
		//! Range: 0.0f to 360.0f (Default: 360.0f)
		virtual void setOuterConeAngle(const float& outerAngle);
		//! Sets how much the volume of the source is scaled in the outer cone
		//! Range: 0.0f to +inf (Default: 0.0f)
		virtual void setOuterConeVolume(const float& outerVolume);

		//! Sets the doppler strength, which enhances or diminishes the doppler effect 
		//! Range: 0.0f to +inf (Default: 1.0f)
		virtual void setDopplerStrength(const float& dstrength); 
		//! Overrides the doppler velocity vector
		virtual void setDopplerVelocity(const cVector3& dvelocity);

		//! Convenience function to automatically set the velocity and position for you in a single call
		//! Velocity will be set to new position - last position
		virtual void move(const cVector3& position);

		//!Returns the audio objects position
		virtual const cVector3 getPosition() const;
		//!Returns the audio objects velocity
		virtual const cVector3 getVelocity() const;
		//!Returns the audio objects direction
		virtual const cVector3 getDirection() const;

		//! Returns the factor used in attenuating the source over distance
		virtual const float getRolloffFactor() const;
		//! Returns the strength of the source
		virtual const float getStrength() const;
		//! Returns the distance from the source where attenuation will begin
		virtual const float getMinDistance() const;
		//! Returns the distance from the source where attenuation will stop
		virtual const float getMaxDistance() const;

		//!Returns the pitch of the source
		virtual const float getPitch() const;
		//!Returns the source volume before attenuation and other effects
		virtual const float getVolume() const;
		//! Returns the minimum volume that the source can be attenuated to
		virtual const float getMinVolume() const;
		//! Returns the maximum volume that the source can achieve
		virtual const float getMaxVolume() const;

		//! Returns the angle of the inner sound cone of the source
		virtual const float getInnerConeAngle() const;
		//! Returns the angle of the outer sound cone of the source
		virtual const float getOuterConeAngle() const;
		//! Returns how much the volume of the source is scaled in the outer cone
		virtual const float getOuterConeVolume() const;

		//!Returns the doppler strength, which enhances or diminishes the doppler effect 
		virtual const float getDopplerStrength() const;
		//!Returns the override for the doppler velocity vector
		virtual const cVector3 getDopplerVelocity() const;

		//!Registers a new event handler to source
		virtual void registerEventHandler(ISourceEventHandler* handler);
		//!Unregisters specified event handler from source
		virtual void unRegisterEventHandler(ISourceEventHandler* handler);
		//!Unregisters all event handlers attached to source
		virtual void unRegisterAllEventHandlers();

#ifdef CAUDIO_EFX_ENABLED
		//! Returns the number of effects at one time this source can support
		virtual unsigned int getNumEffectSlotsAvailable() const;
		//! Attaches an EFX audio effect to this sound source to a specific slot
		//! Range (slot): 0 to getNumEffectSlotsAvailable()
		virtual bool attachEffect(unsigned int slot, IEffect* effect);
		//! Removes an EFX audio effect from this sound source
		//! Range (slot): 0 to getNumEffectSlotsAvailable()
		virtual void removeEffect(unsigned int slot);

		//! Attaches an audio filter to this sound source that will operate on the direct feed, seperate from any effects
		virtual bool attachFilter(IFilter* filter);
		//! Removes the previously attached filter
		virtual void removeFilter();
#endif

	protected:
	private:
		//Mutex for thread syncronization
		cAudioMutex Mutex;
		//Empties the current working buffer queue
		void empty();
		//Checks for OpenAL errors and reports them
		bool checkError();
		//Streams audio data from the decoder into a buffer
		bool stream(ALuint buffer);
		//Signals a event to all event handlers
		void signalEvent(Events sevent);
		//Converts our audio format enum to OpenAL's
		ALenum convertAudioFormatEnum(AudioFormats format);

		//The context that owns this source
		ALCcontext* Context;

		//Internal audio buffers
		ALuint Buffers[CAUDIO_SOURCE_NUM_BUFFERS]; 
		//OpenAL source
		ALuint Source; 
		//cAudio decoder being used to stream data
		IAudioDecoder* Decoder;

		//Stores whether the source is to loop the audio stream
		bool Loop;
		//Stores whether the source is ready to be used
		bool Valid;

		std::list<ISourceEventHandler*> eventHandlerList;

#ifdef CAUDIO_EFX_ENABLED
		//Holds pointers to all the EFX related functions
		cEFXFunctions* EFX;
		//Updates the attached filter
		void updateFilter(bool remove = false);
		//Updates the effect attached to a specific slot
		void updateEffect(unsigned int slot, bool remove = false);

		//Stores the effects attached to this source
		IEffect* Effects[CAUDIO_SOURCE_MAX_EFFECT_SLOTS];
		unsigned int LastEffectTimeStamp[CAUDIO_SOURCE_MAX_EFFECT_SLOTS];

		//Stores the attached direct feed filter
		IFilter* Filter;
		unsigned int LastFilterTimeStamp;

		//Number of effects supported by the OpenAL Context
		unsigned int EffectSlotsAvailable;
#endif
    };
};
#endif //! CAUDIOSOURCE_H_INCLUDED
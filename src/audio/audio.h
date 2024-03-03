#ifndef AUDIO_AUDIO_H_
#define AUDIO_AUDIO_H_

#include <vector>
#include <memory>
#include <filesystem>
#include <glm/glm.hpp>
#include "../typedefs.h"

namespace fs = std::filesystem;

namespace audio {
    using speakerid_t = int64_t;
    /// @brief duration unit is second
    using duration_t = double;

    constexpr inline int PRIORITY_LOW = 0;
    constexpr inline int PRIORITY_NORMAL = 5;
    constexpr inline int PRIORITY_HIGH = 10;

    class Speaker;

    /// @brief Audio speaker states
    enum class State {
        playing,
        paused,
        stopped
    };

    /// @brief Pulse-code modulation data
    struct PCM {
        /// @brief May contain 8 bit and 16 bit PCM data
        std::vector<char> data;
        size_t totalSamples;
        uint8_t channels;
        uint8_t bitsPerSample;
        uint sampleRate;
        bool seekable;

        PCM(  
            std::vector<char> data,
            size_t totalSamples,
            uint8_t channels,
            uint8_t bitsPerSample,
            uint sampleRate,
            bool seekable
        ) : data(std::move(data)),
            totalSamples(totalSamples),
            channels(channels), 
            bitsPerSample(bitsPerSample),
            sampleRate(sampleRate),
            seekable(seekable) {}

        inline size_t countSamplesMono() const {
            return totalSamples / channels;
        }

        inline duration_t getDuration() const {
            return static_cast<duration_t>(countSamplesMono()) / 
                   static_cast<duration_t>(sampleRate);
        }
    };

    /// @brief audio::PCMStream is a data source for audio::Stream
    class PCMStream {
    public:
        virtual ~PCMStream() {};

        /// @brief Read samples data to buffer
        /// @param buffer destination buffer
        /// @param bufferSize destination buffer size
        /// @param loop loop stream (seek to start when end reached)
        /// @return size of data received 
        /// (always equals bufferSize if seekable and looped)
        virtual size_t readFully(char* buffer, size_t bufferSize, bool loop);

        virtual size_t read(char* buffer, size_t bufferSize) = 0;

        /// @brief Close stream
        virtual void close()=0;

        /// @brief Check if stream is open
        virtual bool isOpen() const=0;

        /// @brief Get total samples number if seekable or 0
        virtual size_t getTotalSamples() const=0;

        /// @brief Get total audio track duration if seekable or 0.0
        virtual duration_t getTotalDuration() const=0;

        /// @brief Get number of audio channels
        /// @return 1 if mono, 2 if stereo
        virtual uint getChannels() const=0;

        /// @brief Get audio sampling frequency
        /// @return number of mono samples per second
        virtual uint getSampleRate() const=0;

        /// @brief Get number of bits per mono sample
        /// @return 8 or 16
        virtual uint getBitsPerSample() const=0;

        /// @brief Check if the stream does support seek feature
        virtual bool isSeekable() const=0;

        /// @brief Move playhead to the selected sample number
        /// @param position selected sample number
        virtual void seek(size_t position) = 0;
    };

    /// @brief Audio streaming interface
    class Stream {
    public:
        virtual ~Stream() {};

        /// @brief Get pcm data source
        /// @return PCM stream or nullptr if audio::openStream 
        /// keepSource argument is set to false
        virtual std::shared_ptr<PCMStream> getSource() const = 0;

        /// @brief Create new speaker bound to the Stream 
        /// and having high priority
        /// @param loop is stream looped (required for correct buffers preload)
        /// @return speaker id or 0
        virtual Speaker* createSpeaker(bool loop) = 0;

        /// @brief Unbind previous speaker and bind new speaker to the stream
        /// @param speaker speaker id or 0 if all you need is unbind speaker
        virtual void bindSpeaker(speakerid_t speaker) = 0;

        /// @brief Get id of the bound speaker
        /// @return speaker id or 0 if no speaker bound
        virtual speakerid_t getSpeaker() const = 0;

        /// @brief Update stream state (preload samples if needed)
        /// @param delta time elapsed since the last update
        virtual void update(double delta) = 0;

        /// @brief Set playhead to the selected time
        /// @param time selected time
        virtual void setTime(duration_t time) = 0;
    };

    /// @brief Sound is an audio asset that supposed to support many 
    /// simultaneously playing instances with different sources.
    /// So it's audio data is stored in memory.
    class Sound {
    public:
        virtual ~Sound() {}

        /// @brief Get sound duration
        /// @return duration in seconds (>= 0.0)
        virtual duration_t getDuration() const = 0;

        /// @brief Get sound PCM data
        /// @return PCM data or nullptr
        virtual std::shared_ptr<PCM> getPCM() const = 0;

        /// @brief Create new sound instance
        /// @param priority instance priority. High priority instance can 
        /// take out speaker from low priority instance
        /// @return new speaker with sound bound or nullptr 
        /// if all speakers are in use
        virtual Speaker* newInstance(int priority) const = 0;
    };

    /// @brief Audio source controller interface
    class Speaker {
    public:
        virtual ~Speaker() {}

        /// @brief Get current speaker state
        /// @return speaker state
        virtual State getState() const = 0;

        /// @brief Get speaker audio gain
        /// @return speaker audio gain value
        virtual float getVolume() const = 0;

        /// @brief Set speaker audio gain (must be positive)
        /// @param volume new gain value
        virtual void setVolume(float volume) = 0;

        /// @brief Get speaker pitch multiplier
        /// @return pitch multiplier
        virtual float getPitch() const = 0;

        /// @brief Set speaker pitch multiplier
        /// @param pitch new pitch multiplier (must be positive)
        virtual void setPitch(float pitch) = 0;

        /// @brief Check if speaker audio is in loop
        /// @return true if audio is in loop
        virtual bool isLoop() const = 0;

        /// @brief Enable/disable audio loop
        /// @param loop loop mode
        virtual void setLoop(bool loop) = 0;

        /// @brief Play, replay or resume audio
        virtual void play() = 0;

        /// @brief Pause playing audio and keep speaker alive
        virtual void pause() = 0;

        /// @brief Stop and destroy speaker
        virtual void stop() = 0;

        /// @brief Check if the speaker has stopped by calling stop()
        virtual bool isStoppedManually() const = 0;
        
        /// @brief Get current time position of playing audio
        /// @return time position in seconds
        virtual duration_t getTime() const = 0;

        /// @brief Set playing audio time position
        /// @param time time position in seconds
        virtual void setTime(duration_t time) = 0;

        /// @brief Set speaker 3D position in the world
        /// @param pos new position
        virtual void setPosition(glm::vec3 pos) = 0;

        /// @brief Get speaker 3D position in the world
        /// @return position
        virtual glm::vec3 getPosition() const = 0;

        /// @brief Set speaker movement velocity used for Doppler effect
        /// @param vel velocity vector
        virtual void setVelocity(glm::vec3 vel) = 0;

        /// @brief Get speaker movement velocity used for Doppler effect
        /// @return velocity vector
        virtual glm::vec3 getVelocity() const = 0;

        /// @brief Get speaker priority
        /// @return speaker priority value
        virtual int getPriority() const = 0;

        /// @brief Determines if the position is relative to the listener
        /// @param relative true - relative to the listener (default: false)
        virtual void setRelative(bool relative) = 0;

        /// @brief Determines if the position is relative to the listener
        virtual bool isRelative() const = 0;

        /// @brief Check if speaker is playing 
        inline bool isPlaying() const {
            return getState() == State::playing;
        }

        /// @brief Check if speaker is paused 
        inline bool isPaused() const {
            return getState() == State::paused;
        }

        /// @brief Check if speaker is stopped 
        inline bool isStopped() const {
            return getState() == State::stopped;
        }
    };

    class Backend {
    public:
        virtual ~Backend() {};

        virtual Sound* createSound(std::shared_ptr<PCM> pcm, bool keepPCM) = 0;
        virtual Stream* openStream(std::shared_ptr<PCMStream> stream, bool keepSource) = 0;
        virtual void setListener(
            glm::vec3 position, 
            glm::vec3 velocity, 
            glm::vec3 lookAt, 
            glm::vec3 up
        ) = 0;
        virtual void update(double delta) = 0;

        /// @brief Check if backend is an abstraction that does not internally
        /// work with actual audio data or play anything
        virtual bool isDummy() const = 0;
    };

    /// @brief Initialize audio system or use no audio mode
    /// @param enabled try to initialize actual audio
    extern void initialize(bool enabled);

    /// @brief Load audio file info and PCM data
    /// @param file audio file
    /// @param headerOnly read header only
    /// @throws std::runtime_error if I/O error ocurred or format is unknown 
    /// @return PCM audio data
    extern PCM* loadPCM(const fs::path& file, bool headerOnly);

    /// @brief Load sound from file
    /// @param file audio file path
    /// @param keepPCM store PCM data in sound to make it accessible with Sound::getPCM
    /// @throws std::runtime_error if I/O error ocurred or format is unknown 
    /// @return new Sound instance
    extern Sound* loadSound(const fs::path& file, bool keepPCM);

    /// @brief Create new sound from PCM data
    /// @param pcm PCM data
    /// @param keepPCM store PCM data in sound to make it accessible with Sound::getPCM
    /// @return new Sound instance 
    extern Sound* createSound(std::shared_ptr<PCM> pcm, bool keepPCM);

    /// @brief Open new PCM stream from file
    /// @param file audio file path
    /// @throws std::runtime_error if I/O error ocurred or format is unknown
    /// @return new PCMStream instance
    extern PCMStream* openPCMStream(const fs::path& file);

    /// @brief Open new audio stream from file
    /// @param file audio file path
    /// @param keepSource store PCMStream in stream to make it accessible with Stream::getSource
    /// @return new Stream instance
    extern Stream* openStream(const fs::path& file, bool keepSource);

    /// @brief Open new audio stream from source
    /// @param stream PCM data source
    /// @param keepSource store PCMStream in stream to make it accessible with Stream::getSource
    /// @return new Stream instance
    extern Stream* openStream(std::shared_ptr<PCMStream> stream, bool keepSource);

    /// @brief Configure 3D listener
    /// @param position listener position
    /// @param velocity listener velocity (used for Doppler effect)
    /// @param lookAt point the listener look at
    /// @param up camera up vector
    extern void setListener(
        glm::vec3 position, 
        glm::vec3 velocity, 
        glm::vec3 lookAt, 
        glm::vec3 up
    );

    /// @brief Play 3D sound in the world
    /// @param sound target sound
    /// @param position sound world position
    /// @param relative position speaker relative to listener
    /// @param volume sound volume [0.0-1.0]
    /// @param pitch sound pitch multiplier [0.0-...]
    /// @param loop loop sound
    /// @param priority sound priority 
    /// (PRIORITY_LOW, PRIORITY_NORMAL, PRIORITY_HIGH)
    /// @return speaker id or 0
    extern speakerid_t play(
        Sound* sound,
        glm::vec3 position,
        bool relative,
        float volume,
        float pitch,
        bool loop,
        int priority
    );

    /// @brief Play stream
    /// @param stream target stream
    /// @param position stream world position
    /// @param relative position speaker relative to listener
    /// @param volume stream volume [0.0-1.0]
    /// @param pitch stream pitch multiplier [0.0-...]
    /// @param loop loop stream
    /// @return speaker id or 0
    extern speakerid_t play(
        std::shared_ptr<Stream> stream,
        glm::vec3 position,
        bool relative,
        float volume,
        float pitch,
        bool loop
    );

    /// @brief Play stream from file
    /// @param file audio file path
    /// @param position stream world position
    /// @param relative position speaker relative to listener
    /// @param volume stream volume [0.0-1.0]
    /// @param pitch stream pitch multiplier [0.0-...]
    /// @param loop loop stream
    /// @return speaker id or 0
    /// @return 
    extern speakerid_t playStream(
        const fs::path& file,
        glm::vec3 position,
        bool relative,
        float volume,
        float pitch,
        bool loop
    );

    /// @brief Get speaker by id
    /// @param id speaker id
    /// @return speaker or nullptr
    extern Speaker* get(speakerid_t id);
    
    /// @brief Update audio streams and sound instanced
    /// @param delta time elapsed since the last update (seconds)
    extern void update(double delta);
    
    /// @brief Finalize audio system
    extern void close();
};

#endif // AUDIO_AUDIO_H_
#include "ofxAudioSequencerTemplate.h"

void ofxAudioSequencerTemplate::setup(float durationInSecs, float bpm) {
    ofSetWindowShape(1600, 1000);
    audio.setup();
    audio.toggleDebugUI();
    setupTimeline(durationInSecs, bpm);
    loadNotesMap();
}

void ofxAudioSequencerTemplate::draw() {
    audio.draw();
    timeline.draw();
}

void ofxAudioSequencerTemplate::exit() {
    audio.exit();
}

void ofxAudioSequencerTemplate::keyPressed(int key){
    audio.keyPressed(key);
}

ofxAudioUnitManager* ofxAudioSequencerTemplate::getAudioUnitManager() {
    return &audio;
}

ofxTimeline* ofxAudioSequencerTemplate::getTimeline() {
    return &timeline;
}

void ofxAudioSequencerTemplate::midiEvent(ofxTLSwitchEventArgs &args) {
    string command = args.switchName + (args.on ? " ON" : " OFF");
    cout << endl << ofGetTimestampString() << endl;
    cout << "switch fired: " << command << endl;
    executeMidiCommand(command);
}

void ofxAudioSequencerTemplate::setupTimeline(float duration, float bpm) {
    timeline.setup();
    timeline.setLoopType(OF_LOOP_NORMAL);
    timeline.setDurationInSeconds(duration);
    timeline.setOffset(ofVec2f(10, 450));
    timeline.setWidth(ofGetWidth() - 400);
    if(bpm > -1) {
        timeline.setShowBPMGrid(true);
        timeline.enableSnapToBPM(true);
        timeline.setBPM(bpm);
    }
    timeline.addSwitches("MIDI events");
    ofAddListener(timeline.events().switched, this, &ofxAudioSequencerTemplate::midiEvent);
}

/* Format can be either: "60 ON", "60 OFF"  etc, or
   "C#5 ON", "C#5 OFF" etc */
void ofxAudioSequencerTemplate::executeMidiCommand(string command, ofxMidiOut *midi) {
    vector<string> args = ofSplitString(command, " ");
    if(args.size() == 2) {
        int parsedNote = midiNote(args.at(0));
        if(args.at(1) == "ON") {
            cout << "Sending MIDI ON: " << parsedNote << endl;
            midi->sendNoteOn(1, parsedNote);
        } else {
            cout << "Sending MIDI OFF: " << parsedNote << endl;
            midi->sendNoteOff(1, parsedNote);
        }
    }
}

void ofxAudioSequencerTemplate::executeMidiCommand(string command) {
    chains = audio.allChains();
    for(int i = 0; i < chains.size(); i++) {
        executeMidiCommand(command, chains.at(i)->midi());
    }
}

int ofxAudioSequencerTemplate::midiNote(string arg) {
    if(arg.length() > 1 && ofToInt(arg) == 0) {
        octave = ofToInt(arg.substr(arg.length() - 1, arg.length()));
        note = notes[arg.substr(0, arg.length() - 1)];
        return note + 12 * octave;
    }
    return ofToInt(arg);
}

void ofxAudioSequencerTemplate::loadNotesMap() {
    notes["C"] = 0;
    notes["C#"] = 1;
    notes["D"] = 2;
    notes["D#"] = 3;
    notes["E"] = 4;
    notes["F"] = 5;
    notes["F#"] = 6;
    notes["G"] = 7;
    notes["G#"] = 8;
    notes["A"] = 9;
    notes["A#"] = 10;
    notes["B"] = 11;
}
/*
 ------------------------------------------------------------------
 StreamPlugin
 Copyright (C) 2021 - present Neuro-Electronics Research Flanders

 This file is part of the Open Ephys GUI
 Copyright (C) 2016 Open Ephys
 ------------------------------------------------------------------

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */


#include "StreamPluginEditor.h"
#include "StreamPlugin.h"


StreamPluginEditor::StreamPluginEditor(GenericProcessor *parentNode, bool useDefaultParameters): GenericEditor(parentNode, useDefaultParameters)
{
    StreamProcessor = (StreamPlugin *)parentNode;

    portEditor = new TextEditor("dataport");
    addAndMakeVisible(portEditor);
    portEditor->setBounds(10, 45, 40, 23);
    portEditor->setText(std::to_string(StreamProcessor->getPort()));

    portButton = new TextButton();
    addAndMakeVisible(portButton);
    portButton->setBounds(10, 85, 40, 23);
    portButton->setButtonText("Set Port");
    portButton->addListener(this);

    channelEditor = new TextEditor("channels");
    addAndMakeVisible(channelEditor);
    channelEditor->setBounds(60, 45, 80, 23);
    channelEditor->setText(StreamProcessor->getChannels());

    channelButton = new TextButton();
    addAndMakeVisible(channelButton);
    channelButton->setBounds(60, 85, 80, 23);
    channelButton->setButtonText("Select channels");
    channelButton->addListener(this);

}

StreamPluginEditor::~StreamPluginEditor()
{
    deleteAllChildren();
}


void StreamPluginEditor::buttonClicked(Button* button)
{
    if (button == portButton)
    {
        String dport = portEditor->getText();
        int dportVal = dport.getIntValue();
        if ( (dportVal == 0) && !dport.containsOnly("0")) {
            // wrong integer input
            CoreServices::sendStatusMessage("Invalid data port value");
            portEditor->setText(std::to_string(StreamProcessor->getPort()));
        }else {
            StreamProcessor->setPort(dportVal);
            CoreServices::sendStatusMessage("ZMQ port updated");
        }
    }
    else if (button == channelButton){
        String dchan = channelEditor->getText();

        std::string dchanValue = dchan.toStdString();
        StreamProcessor->setChannels(dchanValue);
        CoreServices::sendStatusMessage("Channel selection updated");
    }
}

void StreamPluginEditor::startAcquisition()
{
    portButton->setEnabled (false);
    portEditor->setEnabled (false);
    channelButton->setEnabled (false);
    channelEditor->setEnabled (false);
}


void StreamPluginEditor::stopAcquisition()
{
    portButton->setEnabled (true);
    portEditor->setEnabled (true);
    channelButton->setEnabled (true);
    channelEditor->setEnabled (true);
}



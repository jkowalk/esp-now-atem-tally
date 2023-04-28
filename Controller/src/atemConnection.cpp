#include "atemConnection.h"

#include <Arduino.h>
#include <SkaarhojPgmspace.h>
#include <ATEMbase.h>
#include <ATEMstd.h>

#include "memory.h"

ATEMstd AtemSwitcher;

int PreviewTallyPrevious = 1;
int ProgramTallyPrevious = 1;
boolean InTransitionPrevious = false;

boolean isInTransition(int transitionPosition)
{
  Serial.print("Transition: ");
  Serial.println(transitionPosition);
  if (transitionPosition > 0 && transitionPosition < 100)
  {
    return true;
  }
  return false;
}

boolean atemIsConnected()
{
  return AtemSwitcher.isConnected();
}

void setupAtemConnection()
{
     // Initialize a connection to the switcher
  AtemSwitcher.begin(switcherIp);
  AtemSwitcher.serialOutput(0x80);
  AtemSwitcher.connect();
}

void atemLoop()
{
   AtemSwitcher.runLoop();

}

boolean checkForAtemChanges()
{
  int ProgramTally = AtemSwitcher.getProgramInput();
  int PreviewTally = AtemSwitcher.getPreviewInput();
  int TransitionPosition = AtemSwitcher.getTransitionPosition();
  boolean InTransition = isInTransition(TransitionPosition);

  Serial.print("Transition: ");
  Serial.println(TransitionPosition);

  if ((ProgramTallyPrevious != ProgramTally) || (PreviewTallyPrevious != PreviewTally) || InTransition != InTransitionPrevious)
  {
    Serial.print("Program: ");
    Serial.println(ProgramTally);
    Serial.print("Preview: ");
    Serial.println(PreviewTally);
    Serial.print("Transition: ");
    Serial.println(InTransition);
    ProgramTallyPrevious = ProgramTally;
    PreviewTallyPrevious = PreviewTally;
    InTransitionPrevious = InTransition;
    return true;
  }
  return false;
}

int getProgramInput()
{
  return AtemSwitcher.getProgramInput();
}

int getPreviewInput()
{
  return AtemSwitcher.getPreviewInput();
}

boolean getTransition()
{
  return isInTransition(AtemSwitcher.getTransitionPosition());
}

String getATEMInformation()
{
  String message = F("ATEM Information:\n\n");
  message += F("getProgramInput: ");
  message += String(AtemSwitcher.getProgramInput());
  message += F("\ngetPreviewInput: ");
  message += String(AtemSwitcher.getPreviewInput());
  for (int i = 1; i < 4; i++)
  {
    message += "\ngetProgramTally " + String(i) + F(": ");
    message += String(AtemSwitcher.getProgramTally(i));
    message += "\ngetPreviewTally " + String(i) + F(": ");
    message += String(AtemSwitcher.getPreviewTally(i));
  }
  message += F("\ngetTransitionPosition: ");
  message += String(AtemSwitcher.getTransitionPosition());
  message += F("\ngetTransitionPreview: ");
  message += String(AtemSwitcher.getTransitionPreview());
  message += F("\ngetTransitionType: ");
  message += String(AtemSwitcher.getTransitionType());
  message += F("\ngetTransitionFramesRemaining0: ");
  message += String(AtemSwitcher.getTransitionFramesRemaining(0));
  message += F("\ngetTransitionMixTime: ");
  message += String(AtemSwitcher.getTransitionMixTime());
  message += F("\ngetFadeToBlackState: ");
  message += String(AtemSwitcher.getFadeToBlackState());
  message += F("\ngetFadeToBlackFrameCount: ");
  message += String(AtemSwitcher.getFadeToBlackFrameCount());
  message += F("\ngetFadeToBlackTime: ");
  message += String(AtemSwitcher.getFadeToBlackTime());

  return message;
}
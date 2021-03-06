// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/shuffleboard/RecordingController.h"

#include "frc/DriverStation.h"

using namespace frc;
using namespace frc::detail;

RecordingController::RecordingController(nt::NetworkTableInstance ntInstance)
    : m_recordingControlEntry(), m_recordingFileNameFormatEntry() {
  m_recordingControlEntry =
      ntInstance.GetEntry("/Shuffleboard/.recording/RecordData");
  m_recordingFileNameFormatEntry =
      ntInstance.GetEntry("/Shuffleboard/.recording/FileNameFormat");
  m_eventsTable = ntInstance.GetTable("/Shuffleboard/.recording/events");
}

void RecordingController::StartRecording() {
  m_recordingControlEntry.SetBoolean(true);
}

void RecordingController::StopRecording() {
  m_recordingControlEntry.SetBoolean(false);
}

void RecordingController::SetRecordingFileNameFormat(wpi::StringRef format) {
  m_recordingFileNameFormatEntry.SetString(format);
}

void RecordingController::ClearRecordingFileNameFormat() {
  m_recordingFileNameFormatEntry.Delete();
}

void RecordingController::AddEventMarker(
    wpi::StringRef name, wpi::StringRef description,
    ShuffleboardEventImportance importance) {
  if (name.empty()) {
    DriverStation::ReportError("Shuffleboard event name was not specified");
    return;
  }
  m_eventsTable->GetSubTable(name)->GetEntry("Info").SetStringArray(
      {description, ShuffleboardEventImportanceName(importance)});
}

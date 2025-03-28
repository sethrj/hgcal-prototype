#include "SiPMSD.hh"

SiPMSD::SiPMSD(G4String name) : G4VSensitiveDetector("SiPMHitCollection")
{
  G4cout << "creating a sensitive detector with name: " << name << G4endl;
  collectionName.insert("SiPMHitCollection");
}

SiPMSD::~SiPMSD() {}

void SiPMSD::Initialize(G4HCofThisEvent* HCE)
{
  hitCollection = new SiPMHitCollection(GetName(), collectionName[0]);

  static G4int HCID = -1;
  if (HCID < 0) HCID = GetCollectionID(0);
  HCE->AddHitsCollection(HCID, hitCollection);

  tmp_hits.clear();
};
void SiPMSD::EndOfEvent(G4HCofThisEvent*)
{
  for (std::map<int, SiPMHit*>::iterator it = tmp_hits.begin(); it != tmp_hits.end(); it++)
    hitCollection->insert(it->second);
};

G4bool SiPMSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  G4double edep = step->GetTotalEnergyDeposit() / CLHEP::keV;  // in keV
  if (edep <= 0)
      return false;

  G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();

  G4int copy_no_cell = touchable->GetVolume(0)->GetCopyNo();
  G4int copy_no_sensor = touchable->GetVolume(1)->GetCopyNo();
  int tmp_ID = 1000 * copy_no_sensor + copy_no_cell;
  if (tmp_hits.find(tmp_ID) == tmp_hits.end()) {  // make new hit
    G4String vol_name = touchable->GetVolume(0)->GetName();
    tmp_hits[tmp_ID] = new SiPMHit(vol_name, copy_no_sensor, copy_no_cell);
    G4double hit_x = (touchable->GetVolume(1)->GetTranslation().x() +
                       touchable->GetVolume(0)->GetTranslation().x()) /
                     CLHEP::cm;
    G4double hit_y = (touchable->GetVolume(1)->GetTranslation().x() +
                       touchable->GetVolume(0)->GetTranslation().y()) /
                     CLHEP::cm;
    G4double hit_z = touchable->GetVolume(1)->GetTranslation().z() / CLHEP::cm;
    tmp_hits[tmp_ID]->SetPosition(hit_x, hit_y, hit_z);  // in cm
  }

  G4double edep_nonIonizing = step->GetNonIonizingEnergyDeposit() / CLHEP::keV;

  G4double timedep = step->GetPostStepPoint()->GetGlobalTime() / CLHEP::ns;

  tmp_hits[tmp_ID]->AddEdep(edep, timedep);
  tmp_hits[tmp_ID]->AddEdepNonIonizing(edep_nonIonizing, timedep);

  return true;
}

#include "CcsIgnoreReader.hh"
#include "LibertyReader.hh"
#include "LibertyReaderPvt.hh"
#include <cstdio>

using namespace sta;
// NOTE: Not using this currently it is parsing by itself
CcsIgnoreReader::CcsIgnoreReader(const char *filename,
                                 bool infer_latches,
                                 sta::Network *network) :
    sta::LibertyReader(filename, infer_latches, network) 
{
    CcsIgnoreReader::defineVisitors();
}
// the core moment:
// call the default visitor setup,
// then swap CCS groups with the ignore-handlers
void CcsIgnoreReader::defineVisitors()
{
    std::cout << "Ovverwitng for CSS" << '\n';


     // then overwrite CCS visitors with CCSN ignore handlers
     // (these handlers already do nothing)
     defineGroupVisitor("output_current_rise",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);

     defineGroupVisitor("output_current_fall",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);

     defineGroupVisitor("normalized_driver_waveform",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);

     defineGroupVisitor("vector",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);

     defineGroupVisitor("receiver_capacitance",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);

     defineGroupVisitor("receiver_capacitance_rise",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);

     defineGroupVisitor("receiver_capacitance_fall",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);

     // attributes to silence
   defineGroupVisitor("receiver_capacitance",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);

   defineGroupVisitor("receiver_capacitance_rise",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);
   defineGroupVisitor("receiver_capacitance_fall",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);
   defineAttrVisitor("segment", &LibertyReader::visitSegement);

   defineGroupVisitor("receiver_capacitance1_rise",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);
   defineGroupVisitor("receiver_capacitance1_fall",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);
   defineGroupVisitor("receiver_capacitance2_rise",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);
   defineGroupVisitor("receiver_capacitance2_fall",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);
   // ccs
   defineGroupVisitor("output_current_rise",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);
   defineGroupVisitor("output_current_fall",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);
   defineGroupVisitor("vector", &LibertyReader::beginVector, &LibertyReader::endVector);
   defineAttrVisitor("reference_time", &LibertyReader::visitReferenceTime);
   defineGroupVisitor("normalized_driver_waveform",
                        &LibertyReader::beginCcsn,
                        &LibertyReader::endCcsn);
   defineAttrVisitor("driver_waveform_name", &LibertyReader::visitDriverWaveformName);
   defineAttrVisitor("driver_waveform_rise", &LibertyReader::visitDriverWaveformRise);
   defineAttrVisitor("driver_waveform_fall", &LibertyReader::visitDriverWaveformFall);

     printf("[ccs-ignore] CCS groups will be ignored.\n");
}


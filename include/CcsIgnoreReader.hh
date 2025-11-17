#ifndef CCS_IGNORE_READER_H
#define CCS_IGNORE_READER_H

#include "LibertyReader.hh"
#include "EnumNameMap.hh"
#include "Report.hh"
#include "Debug.hh"
#include "TokenParser.hh"
#include "Units.hh"
#include "Transition.hh"
#include "FuncExpr.hh"
#include "TimingArc.hh"
#include "TableModel.hh"
#include "LeakagePower.hh"
#include "InternalPower.hh"
#include "LinearModel.hh"
#include "Wireload.hh"
#include "EquivCells.hh"
#include "LibExprReader.hh"
#include "Liberty.hh"
#include "LibertyBuilder.hh"
#include "LibertyReaderPvt.hh"
#include "PortDirection.hh"
#include "ParseBus.hh"
#include "Network.hh"

// a lil shadow-clone of LibertyReader
// that quietly swallows all CCS noise
class CcsIgnoreReader : public sta::LibertyReader {
public:
    CcsIgnoreReader(const char *filename,
                    bool infer_latches,
                    sta::Network *network);
protected:
    // override the spellbook where visitors get registered
    void defineVisitors();
};

#endif // CCS_IGNORE_READER_H


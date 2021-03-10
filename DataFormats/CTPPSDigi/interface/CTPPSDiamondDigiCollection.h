#ifndef CTPPS_CTPPSDigi_CTPPSDiamondDigiCollection_h
#define CTPPS_CTPPSDigi_CTPPSDiamondDigiCollection_h

#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"
#include <vector>
#include <map>
#include <utility>

class CTPPSDiamondDigiCollection {
public:
  typedef std::vector<CTPPSDiamondDigi>::const_iterator ContainerIterator;
  typedef std::pair<ContainerIterator, ContainerIterator> Range;
  typedef std::pair<unsigned int, unsigned int> IndexRange;
  typedef std::map<unsigned int, IndexRange> Registry;
  typedef std::map<unsigned int, IndexRange>::const_iterator RegistryIterator;

  CTPPSDiamondDigiCollection() {}

  void put(Range input, unsigned int detID);
  const Range get(unsigned int detID) const;
  const std::vector<unsigned int> detIDs() const;

private:
  std::vector<CTPPSDiamondDigi> container_;
  Registry map_;
};

#endif

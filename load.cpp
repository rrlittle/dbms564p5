#include <unistd.h>
#include <fcntl.h>
#include "catalog.h"
#include "utility.h"


//
// Loads a file of (binary) tuples from a standard file into the relation.
// Any indices on the relation are updated appropriately.
//
// Returns:
// 	OK on success
// 	an error code otherwise
//

const Status UT_Load(const string & relation, const string & fileName)
{
  Status status;
  RelDesc rd;
  AttrDesc *attrs;
  int attrCnt;
  InsertFileScan * ifs;
  int width = 0;

  if (relation.empty() || fileName.empty() || relation == string(RELCATNAME)
      || relation == string(ATTRCATNAME))
    return BADCATPARM;

  // open Unix data file

  int fd;
  if ((fd = open(fileName.c_str(), O_RDONLY, 0)) < 0)
    return UNIXERR;

  // get relation data
	status = relCat->getInfo(relation, rd);
	if(status != OK){return status;}
	
	

  // start insertFileScan on relation
	ifs = new InsertFileScan(relation, status);
	if(status != OK){return status;}
	
	


  // allocate buffer to hold record read from unix file
  char *record;
  if (!(record = new char [width])) return INSUFMEM;

  int records = 0;
  int nbytes;
  Record rec;

  // read next input record from Unix file and insert it into relation
  while((nbytes = read(fd, record, width)) == width) {
    RID rid;
    rec.data = record;
    rec.length = width;
    if ((status = ifs->insertRecord(rec, rid)) != OK) return status;
    records++;
  }

  // close heap file and unix file
  if (close(fd) < 0) return UNIXERR;

  return OK;
}


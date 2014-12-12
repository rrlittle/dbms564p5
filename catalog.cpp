#include "catalog.h"


RelCatalog::RelCatalog(Status &status) :
	 HeapFile(RELCATNAME, status)
{
// nothing should be needed here
}

//TODO check for multiple returns
const Status RelCatalog::getInfo(const string & relName, RelDesc &record)
{
  if (relName.empty())
    return BADCATPARM;

  Status status;
  Record rec;
  RID rid;
  HeapFileScan * hfs;

	//open a new heapfile scan
	hfs = new HeapFileScan(relName, status);
	if(status != OK){return status;}
	
	status = hfs->startScan(0, //const int offset, 0 for the first attribute
                           	MAXNAME,//const int length, 
                           	STRING,//const Datatype type, attribute 1 is a string 
                           	(const char *)&relName,//const char* filter, scan over records the first record matching relName. 
                           	EQ//const Operator op, we are checking for equality
        										);
        //go to the next record
        status = hfs->scanNext(rid);
        if(status != OK){return status;}
        //get the record. 
        //rec now points to the record and rid points to its rid
        status = hfs->getRecord(rec);
        if(status != OK){return status;}
        
        record = *(RelDesc *) memcpy(&record, &rec, sizeof(Record)); //copy the data to record without returning  apointer to the actual record. 
        
        //close the scan
        status = hfs->endScan();
        if(status != OK){return status;}
  			      
        //everything executed ok
        return OK;
		
}


const Status RelCatalog::addInfo(RelDesc & recDesc)
{
  RID rid;
  InsertFileScan*  ifs;
  Status status;
  Record rec;
  
  //start a new insert filescan to manage inserting the record
  ifs = new InsertFileScan(RELCATNAME, status);
  
  rec.data = &recDesc;
  rec.length = sizeof(recDesc);
  
  //insetr the record into relCat
  status = ifs->insertRecord(rec, rid);
  if(status != OK){return status;}

	///everything returned OK
  return OK;

}

//TODO check for returning multiples
const Status RelCatalog::removeInfo(const string & relName)
{
  Status status;
  RID rid;
  HeapFileScan*  hfs;

  if (relName.empty()) return BADCATPARM;

	//open a new heapfile scan
	hfs = new HeapFileScan(RELCATNAME, status);
	if(status != OK){return status;}

	
	status = hfs->startScan(0, //const int offset, 0 for the first attribute
                         	MAXNAME,//const int length, 
                         	STRING,//const Datatype type, attribute 1 is a string 
                         	(const char *)&relName,//const char* filter, scan over all the tuples matching relName. 
                         	EQ//const Operator op, we are checking for equality
  												);
  												
   //go to the next record
  status = hfs->scanNext(rid);
  if(status != OK){return status;}
	
	status = hfs->deleteRecord();
  if(status != OK){return status;}
	
	//CLOSE HFS
	status = hfs->endScan();
  if(status != OK){return 
	
	
	//everything returned ok
	return OK;	
}


RelCatalog::~RelCatalog()
{
// nothing should be needed here
}


AttrCatalog::AttrCatalog(Status &status) :
	 HeapFile(ATTRCATNAME, status)
{
// nothing should be needed here
}


const Status AttrCatalog::getInfo(const string & relation, 
				  const string & attrName,
				  AttrDesc &record)
{

  Status status;
  RID rid;
  Record rec;
  HeapFileScan*  hfs;

  if (relation.empty() || attrName.empty()) return BADCATPARM;

	
	
	  
  
  



}


const Status AttrCatalog::addInfo(AttrDesc & record)
{
  RID rid;
  InsertFileScan*  ifs;
  Status status;





}


const Status AttrCatalog::removeInfo(const string & relation, 
			       const string & attrName)
{
  Status status;
  Record rec;
  RID rid;
  AttrDesc record;
  HeapFileScan*  hfs;

  if (relation.empty() || attrName.empty()) return BADCATPARM;

}


const Status AttrCatalog::getRelInfo(const string & relation, 
				     int &attrCnt,
				     AttrDesc *&attrs)
{
  Status status;
  RID rid;
  Record rec;
  HeapFileScan*  hfs;

  if (relation.empty()) return BADCATPARM;




}


AttrCatalog::~AttrCatalog()
{
// nothing should be needed here
}


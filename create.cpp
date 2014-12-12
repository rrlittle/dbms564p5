#include "catalog.h"


const Status RelCatalog::createRel(const string & relName, 
				   const int attrCnt,
				   const attrInfo attrList[])
{
  Status status;
  RelDesc rd;
  AttrDesc ad;
  Record rec;
  HeapFile hf;

  if (relation.empty() || attrCnt < 1)
    return BADCATPARM;

  if (relation.length() >= sizeof rd.relName)
    return NAMETOOLONG;

//check if relation already exists. 
	status = relCat->getInfo(relName, &rec);
	if(status == FILEEOF){//if it does not exist
		
		//initialize relDesc. 
		rd.relname = relName;
		rd.attrCnt = attrCnt;
		
		status = relCat->addInfo(&rd);
		if(status != OK){return status;}
		
		int cnt;
		for (cnt = 0; cnt < attrCnt; cnt++){
			//initialize attrDesc
				ad.relName = attrList[cnt].attrName;
				ad.attrName = attrList[cnt].attrName;
				ad.attrOffset = cnt * sizeof(attrList[cnt].attrType);
				ad.attrLen = attrList[cnt].attrLen;
				
				//insert the newly initialized attrDesc
				status = attrCat->addInfo(&ad);
				if(status != OK){return status;}
		} 
		
		//each relation is a table, so it needs a corresponding file to store tuples. 
		hf = new HeapFile(relName, &status);
		if(status != OK){return status;}
		
		
		return OK;
		
	}
	else if(status == OK){ //if it already exist
		return RELEXISTS;
	}
	else{ //something else went wrong. 
		return status;
	}
	




}


package eu.baltrad.example;

import java.util.ArrayList;
import java.util.List;

import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

import eu.baltrad.bdb.db.FileEntry;
import eu.baltrad.bdb.oh5.Metadata;
import eu.baltrad.bdb.oh5.TemplateMetadataNamer;
import eu.baltrad.bdb.util.Date;
import eu.baltrad.bdb.util.Time;
import eu.baltrad.beast.ManagerContext;
import eu.baltrad.beast.db.Catalog;
import eu.baltrad.beast.db.CatalogEntry;
import eu.baltrad.beast.message.IBltMessage;
import eu.baltrad.beast.rules.IScriptableRule;

import eu.baltrad.beast.message.mo.BltDataMessage;
import eu.baltrad.beast.message.mo.BltGenerateMessage;

class Hello implements IScriptableRule {
  private static String[] SUPPORTED_RADARS = ["seang","searl"];
  private Logger logger = LogManager.getLogger(Hello.class);
	
  public Hello() {
  }
	
  private String getSupportedSource(String source) {
    if (source != null) {
      for (String s : SUPPORTED_RADARS) {
        if (s.equals(source)) {
          return s;
        }
      }
    }
    return null;
  }

  @Override
  public IBltMessage handle(IBltMessage bltmsg) {
    BltGenerateMessage result = null;
    if (bltmsg != null && bltmsg instanceof BltDataMessage) {
      FileEntry fe = ((BltDataMessage)bltmsg).getFileEntry();
      String object = fe.getMetadata().getWhatObject();
      if (object != null && (object.equals("PVOL") || object.equals("SCAN"))) {
        Metadata metadata = fe.getMetadata();
	String source = getSupportedSource(metadata.getAttribute("/_bdb/source_name").toString());
	if (source != null) {
          Catalog cat = ManagerContext.getCatalog();
          result = new BltGenerateMessage();
          result.setAlgorithm("eu.baltrad.beast.hello");
          // This type of call to setFiles requires that files are available locally on file system.
          // You can also just specify the uuids, but then you will have to adjust the plugin to use
          // the rave_bdb class for accessing the bdb files.
          result.setFiles([cat.getFileCatalogPath(fe.getUuid().toString())] as String[]);
          result.setArguments(["--arg1=value1","--arg2=value2"] as String[]);
        }
      }
    }
    return result;
  }
}



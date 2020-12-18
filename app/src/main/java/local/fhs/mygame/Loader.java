package local.fhs.mygame;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.logging.Logger;

import android.content.res.AssetManager;

public class Loader {
    private static Logger logger = Logger.getLogger(Loader.class.getName());
    private static AssetManager assetManager = null;

    public static byte[] loadFile(String filename) {
        if (assetManager != null) {
            try {
                // In Java 9 könnte man einfach "inputStream.readAllBytes()" verwenden

                ByteArrayOutputStream baos = new ByteArrayOutputStream();
                InputStream is = assetManager.open(filename);

                // Das könnte man schneller machen, indem man zB chunks von 4 KiB liest
                // (man muss dann den return-Wert behandeln, weil der letzte chunk
                // wahrscheinlich kleiner ist als 4 KiB -- einfach weniger schreiben)
                int c;
                do {
                    c = is.read();
                    if (c != -1) {
                        baos.write(c);
                    }
                } while (c != -1);
                is.close();
                return baos.toByteArray();
            } catch (IOException e) {
                logger.warning("Error: " + e);
            }
        }

        return new byte[0];
    }

    public static void setAssetManager(AssetManager assets) {
        assetManager = assets;
    }
}

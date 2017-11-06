package joe.com.ndktutorial.activity;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

import java.io.File;

import joe.com.ndktutorial.R;

/**
 * JNI读写文件
 * Created by joe on 2017/11/3.
 */
public class Tutorial4Activity extends AppCompatActivity {

    private TextView textView;

    String filePath;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tutorial_4);
        textView = (TextView) findViewById(R.id.tv_tutorial_4);
        filePath = (new File(getExternalCacheDir(), "tutorial4.txt")).getAbsolutePath();
        findViewById(R.id.btn_tutorial_4_1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String s = readFromFile(filePath);
                textView.setText(s);
            }
        });

        findViewById(R.id.btn_tutorial_4_2).setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                writeToFile(filePath, "HELLO WORLD");
            }
        });
    }

    static {
        System.loadLibrary("tutorial-4");
    }

    private native void writeToFile(String file, String content);

    private native String readFromFile(String file);
}

package joe.com.ndktutorial.activity;

import android.os.Bundle;
import android.os.Handler;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import joe.com.ndktutorial.R;

/**
 * Jni socket通信
 * Created by joe on 2017/11/3.
 */
public class Tutorial5Activity extends AppCompatActivity {

    private TextView receiveTv;
    private EditText contentEdt;
    private Handler mHandler;
    private boolean isStart = false;
    private Button serverBtn;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tutorial_5);
        receiveTv = (TextView) findViewById(R.id.tv_tutorial_5);
        contentEdt = (EditText) findViewById(R.id.edt_tutorial_5);

        serverBtn = (Button) findViewById(R.id.btn_tutorial_5_1);
        serverBtn.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                if (!isStart) {
                    if (startServer() == 0) {
                        serverBtn.setText("stopServer");
                        isStart = true;
                    }
                } else {
                    stopServer();
                    serverBtn.setText("startServer");
                    isStart = false;
                }
            }
        });
        findViewById(R.id.btn_tutorial_5_2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startClient();
            }
        });

        findViewById(R.id.btn_tutorial_5_3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (contentEdt != null) {
                    String s = contentEdt.getText().toString();
                    sendMsg(s);
                }
            }
        });
        mHandler = new Handler();
    }

    public void setReceiveContent(final String content) {
        if (mHandler != null) {
            mHandler.post(new Runnable() {
                @Override
                public void run() {
                    receiveTv.setText(content);
                }
            });
        }
    }

    private native int startServer();

    private native void stopServer();

    private native void startClient();

    private native void sendMsg(String content);

    static {
        System.loadLibrary("tutorial-5");
    }
}

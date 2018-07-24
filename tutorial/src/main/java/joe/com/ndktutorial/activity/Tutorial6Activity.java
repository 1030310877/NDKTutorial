package joe.com.ndktutorial.activity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.ImageView;

import joe.com.ndktutorial.R;

public class Tutorial6Activity extends AppCompatActivity {
    private ImageView grayImageView;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tutorial_6);
        grayImageView = (ImageView) findViewById(R.id.imageView2);
        Bitmap bmp = BitmapFactory.decodeResource(getResources(), R.drawable.ddd);
        Log.d("Tutorial6Activity", "onCreate1: " + System.currentTimeMillis());
        grayBitmap(bmp);
        Log.d("Tutorial6Activity", "onCreate2: " + System.currentTimeMillis());
        grayImageView.setImageBitmap(bmp);
    }

    static {
        System.loadLibrary("tutorial-6");
    }

    private static native Bitmap grayBitmap(Bitmap bmp);
}

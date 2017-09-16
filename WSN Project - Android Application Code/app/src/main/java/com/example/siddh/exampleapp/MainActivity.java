package com.example.siddh.exampleapp;

import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.speech.RecognizerIntent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {
    private WebView mWebView;
    static final int REQ_CODE_SPEECH_INPUT=1;
    String url="http://wsn-enigmasidd.c9users.io";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button button = (Button) findViewById(R.id.reload_btn);
        mWebView = (WebView) findViewById(R.id.webView);
        mWebView.clearCache(true);
        mWebView.loadUrl(url);
        mWebView.getSettings().setJavaScriptEnabled(true);
        mWebView.getSettings().setDomStorageEnabled(true);
        mWebView.getSettings().setPluginState(WebSettings.PluginState.ON);
        mWebView.setInitialScale(100);
        this.mWebView.setWebViewClient(new WebViewClient() {

            @Override
            public boolean shouldOverrideUrlLoading(WebView view, String url) {
                view.clearCache(true);
                view.loadUrl(url);
                return true;
            }
        });
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                mWebView.loadUrl( "javascript:window.location.reload( true )" );
            }
        });
    }
 /*   protected void AcceptSpeech(){
        //start the RecognizerIntent
        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,
                RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);     // two params available 1. free form and 2. web search
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());  //Optional IETF language tag-for example "en-US". "en-IN"
        intent.putExtra(RecognizerIntent.EXTRA_PROMPT,
                "Say Something");
        try {
            startActivityForResult(intent, REQ_CODE_SPEECH_INPUT);
        } catch (ActivityNotFoundException a) {
            Toast.makeText(getApplicationContext(),
                    "Speech not suported",
                    Toast.LENGTH_SHORT).show();
        }
    }*/

/*    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (requestCode) {
            case REQ_CODE_SPEECH_INPUT: {
                if (resultCode == RESULT_OK && null != data) {

                    ArrayList<String> result = data
                            .getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
                   String ss;
        ss = result.get(0);  //get the first result


    }
    break;

}
}


        }*/
}
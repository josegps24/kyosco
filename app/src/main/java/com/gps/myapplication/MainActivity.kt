package com.gps.myapplication

import android.os.Bundle
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.gps.myapplication.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity(), View.OnClickListener {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.btnRead.setOnClickListener(this)
        binding.btnWrite.setOnClickListener(this)



       //setPermission()
        // Example of a call to a native method
        //binding.sampleText.text = stringFromJNI()
    }


    override fun onClick(p0: View?) {
        val id = p0?.id
        when(id){
            binding.btnRead.id->{
                getGPIOValue()
            }

            binding.btnWrite.id->{
                setGPIOValue()
            }
        }
    }


    /**
     * Set el valor de gpio numero
     */
    private fun setGPIOValue() {
        val numGpio = binding.etGpionum.text.toString()
        val valueGpio = binding.etGpiovalue.text.toString()
        if (numGpio.isEmpty()){
            Toast.makeText(applicationContext, "Ingrese numero de GPIO", Toast.LENGTH_SHORT).show()
            return
        }
        if (valueGpio.isEmpty()){
            Toast.makeText(applicationContext, "Ingrese valor para GPIO", Toast.LENGTH_SHORT).show()
        }

        val resultGpio:Int = setGPIOValue(numGpio.toInt(), valueGpio.toInt())

        if(0!=resultGpio){
            Toast.makeText(applicationContext, "Error al escribir el pin GPIO", Toast.LENGTH_SHORT).show()
        }else{
            Toast.makeText(applicationContext, "Se escribio con éxito", Toast.LENGTH_SHORT).show()
        }



    }




    /**
     * Capturamos el valor de Gpio
     */
    private fun getGPIOValue() {
        val numGpio = binding.etGpionum.text.toString()
        if (numGpio.isEmpty()){
            Toast.makeText(applicationContext, "Digite un numero gpio", Toast.LENGTH_SHORT).show()
            return
        }
        val gpioNum = numGpio.toInt()
        val value = getGPIOValue(gpioNum)
        if (-1!=value){
            binding.tvGpiovalue.setText("GPIO ${gpioNum} value is: $value")
        }else{
            binding.tvGpiovalue.text = "Error en lectura de GPIO.."
        }

    }


    /**
     * A native method that is implemented by the 'myapplication' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun getGPIOValue(gpioNum:Int):Int
    external fun setGPIOValue(gpioNum:Int,value:Int):Int
    external fun setPermission():Int

    companion object {
        // Used to load the 'myapplication' library on application startup.
        init {
            System.loadLibrary("myapplication")
        }
    }




}
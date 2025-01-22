package ecosystem.visual;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

/** See {@link ChangeListener}. */
public class SliderManager implements ChangeListener
{
    public void stateChanged(ChangeEvent e)
    {
        JSlider source = (JSlider)e.getSource();

        if(!source.getValueIsAdjusting())
            sliderValue = source.getValue();
    }

    public int getSliderValue() { return sliderValue; }

    /** Returns specific values based around Ecosystem cycle speed. */
    public int getCustomSliderValue()
    {
        if(sliderValue == 1)
            return 400;
        if(sliderValue < 41)
            return Math.abs(sliderValue - 40) + 4;
        return sliderValue - 40;
    }

    //Fields
    int sliderValue;
}

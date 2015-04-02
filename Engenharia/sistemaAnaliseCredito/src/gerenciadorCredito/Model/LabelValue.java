/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Model;

/**
 *
 * @author vanderson
 */
public class LabelValue {
    private int value = 0;
    private String label = "";

    public LabelValue(String label, int value){
        this.label = label;
        this.value = value;
    }
    
    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public String getLabel() {
        return label;
    }

    public void setLabel(String label) {
        this.label = label;
    }
    
}

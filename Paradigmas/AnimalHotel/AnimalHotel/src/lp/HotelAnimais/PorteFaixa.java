/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package lp.HotelAnimais;

/**
 *
 * @author vanderson
 */
public class PorteFaixa {

    private Double alturaInicial;
    private Double alturaFinal;
    private Double comprimentoInicial;
    private Double comprimentoFinal;
    private Especie especie;
    private Porte porte;

    public PorteFaixa(Double alturaInicial, Double alturaFinal,
            Double comprimentoInicial, Double comprimentoFinal,
            Especie especie, Porte porte) {
        super();
        this.alturaInicial = alturaInicial;
        this.alturaFinal = alturaFinal;
        this.comprimentoInicial = comprimentoInicial;
        this.comprimentoFinal = comprimentoFinal;
        this.especie = especie;
        this.porte = porte;
    }

    // métodos get e set
    public Double getAlturaInicial() {
        return alturaInicial;
    }

    public void setAlturaInicial(Double alturaInicial) {
        this.alturaInicial = alturaInicial;
    }

    public Double getAlturaFinal() {
        return alturaFinal;
    }

    public void setAlturaFinal(Double alturaFinal) {
        this.alturaFinal = alturaFinal;
    }

    public Double getComprimentoInicial() {
        return comprimentoInicial;
    }

    public void setComprimentoInicial(Double comprimentoInicial) {
        this.comprimentoInicial = comprimentoInicial;
    }

    public Double getComprimentoFinal() {
        return comprimentoFinal;
    }

    public void setComprimentoFinal(Double comprimentoFinal) {
        this.comprimentoFinal = comprimentoFinal;
    }

    public Especie getEspecie() {
        return especie;
    }

    public void setEspecie(Especie especie) {
        this.especie = especie;
    }

    public Porte getPorte() {
        return porte;
    }

    public void setPorte(Porte porte) {
        this.porte = porte;
    }

    /**
     * Verifica se o animal informado é do porte dessa faixa de valores (altura
     * e comprimento).
     */
    public boolean isAnimalDessePorte(Animal animal) {
        if (animal.getEspecie() == especie) {
            if (animal.getAltura() >= alturaInicial
                    && animal.getAltura() < alturaFinal) {
                return true;
            } else if (animal.getComprimento() >= comprimentoInicial
                    && animal.getComprimento() < comprimentoFinal) {
                return true;
            } else {
                return false;
            }
        }else{
            return false;
        }
    }
}

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Model;

import java.io.File;
import java.math.BigDecimal;
import java.util.Date;
import org.jrimum.bopepo.BancosSuportados;
import org.jrimum.bopepo.Boleto;
import org.jrimum.bopepo.view.BoletoViewer;
import org.jrimum.domkee.comum.pessoa.endereco.Endereco;
import org.jrimum.domkee.comum.pessoa.endereco.UnidadeFederativa;
import org.jrimum.domkee.financeiro.banco.ParametrosBancariosMap;
import org.jrimum.domkee.financeiro.banco.febraban.Agencia;
import org.jrimum.domkee.financeiro.banco.febraban.Carteira;
import org.jrimum.domkee.financeiro.banco.febraban.Cedente;
import org.jrimum.domkee.financeiro.banco.febraban.ContaBancaria;
import org.jrimum.domkee.financeiro.banco.febraban.NumeroDaConta;
import org.jrimum.domkee.financeiro.banco.febraban.Sacado;
import org.jrimum.domkee.financeiro.banco.febraban.TipoDeTitulo;
import org.jrimum.domkee.financeiro.banco.febraban.Titulo;

/**
 *
 * @author vandersonmr
 */
public class GeradorDeBoletos {

    public File gerarBolet(BoletoARI boleto) {
        Cedente cedente = new Cedente("ARI Soluções", "51.156.642/0001-15");
                
        Sacado sacado = new Sacado(boleto.getNome(), boleto.getCpf());
        Endereco enderecoSac = new Endereco();
        enderecoSac.setUF(UnidadeFederativa.PR);
        enderecoSac.setBairro("Zona 07");
        enderecoSac.setLogradouro("Rua Mandaguari");
        enderecoSac.setNumero("10");
        enderecoSac.setLocalidade(boleto.getEndereco());
        enderecoSac.setCep(boleto.getCep());
        sacado.addEndereco(enderecoSac);
        ContaBancaria contaBancaria = null;
        if (boleto.getBanco().equalsIgnoreCase("caixa")) {
            contaBancaria = new ContaBancaria(BancosSuportados.CAIXA_ECONOMICA_FEDERAL.create());
        } else if (boleto.getBanco().equalsIgnoreCase("banco do brasil")) {
            contaBancaria = new ContaBancaria(BancosSuportados.BANCO_DO_BRASIL.create());
        } else if (boleto.getBanco().equalsIgnoreCase("itaú")) {
            contaBancaria = new ContaBancaria(BancosSuportados.BANCO_ITAU.create());
        }


        contaBancaria.setNumeroDaConta(new NumeroDaConta(12345, "0"));
        contaBancaria.setCarteira(new Carteira(8));
        contaBancaria.setAgencia(new Agencia(0001, "1"));

        Titulo titulo = new Titulo(contaBancaria, sacado, cedente);
        titulo.setNumeroDoDocumento("12345");
        titulo.setNossoNumero("99345678943143");
        titulo.setDigitoDoNossoNumero("5");
        titulo.setValor(BigDecimal.valueOf(boleto.getValor()));
        titulo.setDataDoDocumento(new Date());
        titulo.setDataDoVencimento(new Date());
        titulo.setTipoDeDocumento(TipoDeTitulo.DM_DUPLICATA_MERCANTIL);
        titulo.setAcrecimo(BigDecimal.ZERO);
        titulo.setValorCobrado(BigDecimal.ZERO);
        titulo.setMora(BigDecimal.ZERO);
        titulo.setDesconto(new BigDecimal(0.00));
        titulo.setAceite(Titulo.Aceite.A);
        
        Boleto boletogerado = new Boleto(titulo);

        boletogerado.setLocalPagamento("Pagável em qualquer banco até a data de vencimento.");
        boletogerado.setInstrucaoAoSacado("Ao efetuar o pagamento, entre em contato com (XX)XXXX-XXXX");
        boletogerado.setInstrucao1("Após o vencimento o boleto deve ser pago no banco especificado.");
        boletogerado.setInstrucao2("A cada dia após o vencimento deve ser acrescida multa de 3%.");

        BoletoViewer boletoViewer = new BoletoViewer(boletogerado);

        File arquivoPdf = boletoViewer.getPdfAsFile("boletoARI.pdf");

        return arquivoPdf;

        //InputStream inputStream = new ByteArrayInputStream(arquivoPdf);


        //result.redirectTo(this.boleto());
    }
}

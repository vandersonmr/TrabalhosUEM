<%-- 
    Document   : gerarBoleto
    Created on : 16/05/2013, 21:30:41
    Author     : vanderson
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js" ></script>
        <script type="text/javascript" src="http://igorescobar.github.io/jQuery-Mask-Plugin/js/jquery.mask.min.js"></script>
        <script src="./mascaras.js"></script>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Sistema de Análise de Crédito</title>
        <style>
            @import url("/WEB-INF/style.css");
        </style>
    </head>
    <body>
        <ul id="menu">
            <li>
                <a href="${pageContext.request.contextPath}/menu">Home</a>
            </li>
            <li>
                <a >Consultas</a>
                <ul>
                    <li>
                        <a href="${pageContext.request.contextPath}/menuConsultaInterna">Servidor Local</a>
                    </li>
                    <li>
                        <a href="${pageContext.request.contextPath}/menuConsultaExterna">Servidor Externo</a>
                    </li>
                </ul>
            <li>
            <li>
                <a href="${pageContext.request.contextPath}/gerarBoleto">Gerar Boleto</a>
            <li>
            <li>
                <a >Gerenciamento de Lojista</a>
                <ul>
                    <li><a href="${pageContext.request.contextPath}/menuNovoCadastro">Novo Cadastro</a></li>
                    <li><a href="${pageContext.request.contextPath}/menuBuscarCadastro">Buscar Cadastro</a></li>
                   <!--<li><a href="${pageContext.request.contextPath}/menuAlterarCadastro">Altera Cadastro</a></li>-->
                </ul>
            <li>
            <li>
                <a href="${pageContext.request.contextPath}/logout">Logout</a>
            <li>
        </ul>
        <form id="gerarBoletoForm" action="${pageContext.request.contextPath}/boleto" method="post">
            <fieldset>
                <legend><h1>Gerador de Boleto da A.R.I Inc</h1></legend>

                <li>
                    <label> Nome*: </label>
                    <input type="text" name="boleto.nome" required><br><br>                    
                    <label> CPF* (000.000.000-00): </label>
                    <input id="cpf" type="text" name="boleto.cpf" pattern="\d{3}\.\d{3}\.\d{3}-\d{2}" required><br><br>
                    <label> Valor*: </label>
                    <input name="boleto.valor" required><br><br>
                    <label> Endereço*: </label>
                    <input type="text" name="boleto.endereco" required> <br><br>
                    <label> CEP*: </label>
                    <input id="cep" type="text" name="boleto.cep" required> <br><br>
                    <label> Banco*: </label>
                    <select name="boleto.banco">
                        <option value="Caixa"> Caixa</option>
                        <option value="Itaú"> Itaú</option>
                        <option value="Banco do Brasil">Banco do Brasil</option>
                        <option value="Bradesco"> Bradesco</option>
                    </select>
                </li>
                <br><br>
                <li>
                    <input type="submit"  class="btn" value="Gerar Boleto"/><br>
                <spam class="required_notification">Itens com * são obrigatórios.</spam>
                </li>
                <br><br>
                Sistema de Análise de Crédito. 2013. Criado pela equipe <a href="sobre.html">Lobos</a>.
            </fieldset>
        </form>
    </body>
</html>
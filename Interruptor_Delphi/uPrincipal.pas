unit uPrincipal;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes, System.Variants,
  FMX.Types, FMX.Controls, FMX.Forms, FMX.Graphics, FMX.Dialogs,
  IdBaseComponent, IdComponent, IdUDPBase, IdUDPClient, FMX.StdCtrls, FMX.Edit,
  FMX.Controls.Presentation, FMX.Layouts;

type
  TForm1 = class(TForm)
    Layout1: TLayout;
    btnConectar: TButton;
    btnON: TButton;
    btnOFF: TButton;
    edtStatus: TEdit;
    btnStatus: TButton;
    edtIP: TEdit;
    edtPorta: TEdit;
    lblIP: TLabel;
    lblPorta: TLabel;
    udp: TIdUDPClient;
    procedure btnConectarClick(Sender: TObject);
    procedure btnONClick(Sender: TObject);
    procedure btnOFFClick(Sender: TObject);
    procedure btnStatusClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.fmx}

procedure TForm1.btnConectarClick(Sender: TObject);
begin
  udp.Host := edtIP.Text;
  udp.Port := edtPorta.Text.ToInteger;
  udp.Active := True;
end;

procedure TForm1.btnOFFClick(Sender: TObject);
begin
  udp.Send('OFF');
end;

procedure TForm1.btnONClick(Sender: TObject);
begin
  udp.Send('OON');
end;

procedure TForm1.btnStatusClick(Sender: TObject);
begin
  udp.Send('STS');
  edtStatus.Text := udp.ReceiveString(3000);
end;

end.

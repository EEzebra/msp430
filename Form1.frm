VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFLXGD.OCX"
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "���������ͨѶ��λ�����V1.0"
   ClientHeight    =   8970
   ClientLeft      =   45
   ClientTop       =   390
   ClientWidth     =   13740
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   8970
   ScaleWidth      =   13740
   StartUpPosition =   3  '����ȱʡ
   Begin VB.TextBox Text6 
      Height          =   1215
      Left            =   6720
      TabIndex        =   21
      Text            =   "Text6"
      Top             =   7440
      Width           =   1815
   End
   Begin VB.CommandButton Command8 
      Caption         =   "�޸�"
      Height          =   375
      Left            =   8880
      TabIndex        =   19
      Top             =   6000
      Width           =   615
   End
   Begin VB.CommandButton Command7 
      Caption         =   "ɾ��"
      Height          =   375
      Left            =   8880
      TabIndex        =   18
      Top             =   5355
      Width           =   615
   End
   Begin MSHierarchicalFlexGridLib.MSHFlexGrid MSHFlexGrid1 
      Height          =   1710
      Left            =   600
      TabIndex        =   17
      Top             =   4680
      Width           =   8295
      _ExtentX        =   14631
      _ExtentY        =   3016
      _Version        =   393216
      _NumberOfBands  =   1
      _Band(0).Cols   =   2
   End
   Begin VB.CommandButton Command6 
      Caption         =   "д��"
      Height          =   375
      Left            =   8640
      TabIndex        =   16
      Top             =   2760
      Width           =   1000
   End
   Begin VB.CommandButton Command5 
      Caption         =   "�������"
      Height          =   390
      Left            =   10440
      TabIndex        =   15
      Top             =   3960
      Width           =   1800
   End
   Begin VB.CommandButton Command4 
      Caption         =   "��ȡ���ݿ�"
      Height          =   375
      Left            =   600
      TabIndex        =   14
      Top             =   1200
      Width           =   1300
   End
   Begin VB.CommandButton Command3 
      Caption         =   "���"
      Height          =   375
      Left            =   8880
      TabIndex        =   13
      Top             =   4680
      Width           =   600
   End
   Begin VB.CommandButton Command2 
      Caption         =   "��������"
      Height          =   375
      Left            =   8640
      TabIndex        =   12
      Top             =   2160
      Width           =   1000
   End
   Begin VB.CommandButton Command1 
      Caption         =   "�������"
      Height          =   375
      Left            =   8640
      TabIndex        =   11
      Top             =   6600
      Width           =   855
   End
   Begin VB.TextBox Text5 
      Height          =   375
      Left            =   600
      TabIndex        =   10
      Text            =   "�������"
      Top             =   2150
      Width           =   1695
   End
   Begin VB.TextBox Text4 
      Height          =   375
      Left            =   4500
      TabIndex        =   9
      Text            =   "��ַ"
      Top             =   2150
      Width           =   3975
   End
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   4920
      TabIndex        =   8
      Text            =   "��ϵ��ʽ"
      Top             =   3360
      Width           =   2055
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   2160
      TabIndex        =   7
      Text            =   "��ַ"
      Top             =   6600
      Width           =   6255
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   600
      TabIndex        =   6
      Text            =   "�ֻ����"
      Top             =   6600
      Width           =   1455
   End
   Begin VB.Timer Timer1 
      Left            =   4680
      Top             =   240
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   3960
      Top             =   240
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.TextBox txtMsg 
      Height          =   1185
      Left            =   2880
      MultiLine       =   -1  'True
      TabIndex        =   5
      Text            =   "Form1.frx":0000
      Top             =   7440
      Width           =   1500
   End
   Begin VB.TextBox txtSend 
      Height          =   1215
      Left            =   480
      MultiLine       =   -1  'True
      TabIndex        =   4
      Text            =   "Form1.frx":0006
      Top             =   7440
      Width           =   2070
   End
   Begin VB.TextBox txtReceive 
      Height          =   1215
      Left            =   4680
      MultiLine       =   -1  'True
      TabIndex        =   3
      Text            =   "Form1.frx":000C
      Top             =   7440
      Width           =   1710
   End
   Begin VB.CommandButton btnOpenSerial 
      Caption         =   "�򿪴���"
      Height          =   550
      Left            =   2040
      TabIndex        =   2
      Top             =   150
      Width           =   975
   End
   Begin VB.CommandButton btnSend_Click 
      Caption         =   "����"
      Height          =   400
      Left            =   9000
      TabIndex        =   1
      Top             =   7440
      Width           =   1000
   End
   Begin VB.ComboBox comPort 
      Height          =   300
      ItemData        =   "Form1.frx":0012
      Left            =   400
      List            =   "Form1.frx":002E
      TabIndex        =   0
      Text            =   "Combo1"
      Top             =   400
      Width           =   1500
   End
   Begin VB.Frame Frame2 
      Caption         =   "�ͻ���Ϣ"
      Height          =   6350
      Left            =   400
      TabIndex        =   22
      Top             =   850
      Width           =   9500
      Begin VB.TextBox Text12 
         Height          =   375
         Left            =   1950
         TabIndex        =   39
         Text            =   "��˾"
         Top             =   1300
         Width           =   2055
      End
      Begin VB.CommandButton Command11 
         Caption         =   "�޸�"
         Height          =   375
         Left            =   3600
         TabIndex        =   27
         Top             =   3240
         Width           =   615
      End
      Begin VB.CommandButton Command10 
         Caption         =   "ɾ��"
         Height          =   375
         Left            =   3600
         TabIndex        =   26
         Top             =   2570
         Width           =   615
      End
      Begin VB.CommandButton Command9 
         Caption         =   "���"
         Height          =   375
         Left            =   3600
         TabIndex        =   25
         Top             =   1920
         Width           =   615
      End
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid MSHFlexGrid2 
         Height          =   1815
         Left            =   195
         TabIndex        =   24
         Top             =   1800
         Width           =   3420
         _ExtentX        =   6033
         _ExtentY        =   3201
         _Version        =   393216
         _NumberOfBands  =   1
         _Band(0).Cols   =   2
      End
      Begin VB.Label Label7 
         Caption         =   "��˾��ַ"
         Height          =   375
         Left            =   4100
         TabIndex        =   42
         Top             =   950
         Width           =   855
      End
      Begin VB.Label Label6 
         Caption         =   "��˾����"
         Height          =   375
         Left            =   2000
         TabIndex        =   41
         Top             =   950
         Width           =   1695
      End
      Begin VB.Label Label5 
         Caption         =   "�������"
         Height          =   255
         Left            =   200
         TabIndex        =   40
         Top             =   950
         Width           =   1335
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "����"
      Height          =   6350
      Left            =   10200
      TabIndex        =   20
      Top             =   850
      Width           =   3255
      Begin VB.CommandButton Command14 
         Caption         =   "���ŷ���"
         Height          =   255
         Left            =   720
         TabIndex        =   44
         Top             =   5880
         Width           =   1695
      End
      Begin VB.CommandButton Command13 
         Caption         =   "ˢ�·ֻ�"
         Height          =   500
         Left            =   1920
         TabIndex        =   38
         Top             =   1680
         Width           =   1000
      End
      Begin VB.TextBox Text11 
         Height          =   375
         Left            =   240
         TabIndex        =   37
         Text            =   "�ֻ���ַ"
         Top             =   2400
         Width           =   2655
      End
      Begin VB.ComboBox SlaveNum 
         Height          =   300
         Left            =   240
         TabIndex        =   36
         Text            =   "Combo1"
         Top             =   1680
         Width           =   1455
      End
      Begin VB.CommandButton Command12 
         Caption         =   "ʱ��ͬ��"
         Height          =   500
         Left            =   1920
         TabIndex        =   35
         Top             =   720
         Width           =   1000
      End
      Begin VB.TextBox Text10 
         Height          =   495
         Left            =   240
         Locked          =   -1  'True
         MultiLine       =   -1  'True
         TabIndex        =   34
         Text            =   "Form1.frx":0062
         Top             =   720
         Width           =   1455
      End
      Begin VB.TextBox Text9 
         Height          =   400
         Left            =   1440
         TabIndex        =   30
         Top             =   5280
         Width           =   1000
      End
      Begin VB.TextBox Text8 
         Height          =   400
         Left            =   1440
         TabIndex        =   29
         Top             =   4560
         Width           =   1000
      End
      Begin VB.TextBox Text7 
         Height          =   400
         Left            =   1440
         TabIndex        =   28
         Top             =   3840
         Width           =   1000
      End
      Begin VB.Shape Shape2 
         FillStyle       =   0  'Solid
         Height          =   375
         Left            =   2400
         Shape           =   4  'Rounded Rectangle
         Top             =   3000
         Width           =   495
      End
      Begin VB.Label Label8 
         Caption         =   "����ʱ��"
         Height          =   375
         Left            =   240
         TabIndex        =   43
         Top             =   360
         Width           =   735
      End
      Begin VB.Label Label4 
         Caption         =   "C���ѹ��"
         Height          =   495
         Left            =   480
         TabIndex        =   33
         Top             =   5280
         Width           =   855
      End
      Begin VB.Label Label3 
         Caption         =   "B���ѹ��"
         Height          =   495
         Left            =   480
         TabIndex        =   32
         Top             =   4560
         Width           =   1095
      End
      Begin VB.Label Label2 
         Caption         =   "A���ѹ��"
         Height          =   375
         Left            =   480
         TabIndex        =   31
         Top             =   3840
         Width           =   975
      End
   End
   Begin VB.Label Label1 
      Caption         =   "���ں�"
      Height          =   250
      Left            =   400
      TabIndex        =   23
      Top             =   150
      Width           =   850
   End
   Begin VB.Shape shpSerial 
      FillStyle       =   0  'Solid
      Height          =   450
      Left            =   3240
      Shape           =   3  'Circle
      Top             =   200
      Width           =   450
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
    Dim conn As ADODB.Connection
    Dim rs As ADODB.Recordset
    Dim conn0 As ADODB.Connection
    Dim rs0 As ADODB.Recordset
    
Private Sub Reshow()

    Set conn = New ADODB.Connection
    
    Set rs = New ADODB.Recordset
    
    
    
    conn.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;" & _
                   "Data Source=" & App.Path & "\DBEmp.mdb;" & _
                   "Persist security Info=False"
    conn.Open
    rs.Open "EmpTable", conn, , adCmdTable
    Set MSHFlexGrid1.DataSource = rs
    rs.Close
    conn.Close

End Sub
Private Sub Reshow0()

    Set conn0 = New ADODB.Connection
    
    Set rs0 = New ADODB.Recordset
    
    
    
    conn0.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;" & _
                   "Data Source=" & App.Path & "\DBEmp.mdb;" & _
                   "Persist security Info=False"
    conn0.Open
    rs0.Open "Phone", conn0, , adCmdTable
    Set MSHFlexGrid2.DataSource = rs0
    rs0.Close
    conn0.Close

End Sub








Private Sub btnOpenSerial_Click()
On Error Resume Next
    Dim baud As String, parity As String, stopbit As String, numBit, comPortNum As Integer
    If btnOpenSerial.Caption = "�򿪴���" Then
        '����ѡ��
        Select Case comPort.ListIndex
            Case -1
                comPortNum = 0
            Case Else
                comPortNum = comPort.ItemData(comPort.ListIndex)
        End Select
        '������ѡ��
                baud = "9600"
        'У�鷽ʽѡ��
                parity = "N"
        'ֹͣλѡ��
                stopbit = "1"
        '����λѡ��
                numBit = "8"
        '��������Ƿ�����
        If comPortNum = 0 Then
            txtMsg.Text = txtMsg.Text + "��ѡ�񴮿�" + Chr(13) + Chr(10)
        End If
        If baud = "" Then
            txtMsg.Text = txtMsg.Text + "��ѡ������" + Chr(13) + Chr(10)
        End If
        If parity = "" Then
            txtMsg.Text = txtMsg.Text + "��ѡ��У��λ" + Chr(13) + Chr(10)
        End If
        If stopbit = "" Then
            txtMsg.Text = txtMsg.Text + "��ѡ��ֹͣλ" + Chr(13) + Chr(10)
        End If
        If numBit = "" Then
            txtMsg.Text = txtMsg.Text + "��ѡ������λ" + Chr(13) + Chr(10)
        End If
        If comPortNum <> 0 And baud <> "" And parity <> "" And stopbit <> "" And numBit <> "" Then
            MSComm1.CommPort = comPortNum
            MSComm1.Settings = baud & "," & parity & "," & numBit & "," & stopbit
            MSComm1.InputMode = comInputModeText
            MSComm1.RThreshold = 1  '���ջ�����ÿ�յ�һ���ַ������¼�onComm()
            MSComm1.PortOpen = True
            If Err.Number = 8002 Then
                txtMsg.Text = "��Ϣ����" & Chr(13) & Chr(10)
                txtMsg.Text = txtMsg.Text + "�˿ڲ�����" + Chr(13) + Chr(10)
                MsgBox "��Ч�Ķ˿ں�", vbOKOnly, "��Ϣ"
                GoTo Label1
            ElseIf Err.Number = 8005 Then
                txtMsg.Text = "��Ϣ����" & Chr(13) & Chr(10)
                txtMsg.Text = txtMsg.Text + "�˿ڱ�ռ��" + Chr(13) + Chr(10)
                MsgBox "�˿ڱ�ռ��", vbOKOnly, "��Ϣ"
                GoTo Label1
            Else
                txtMsg.Text = "��Ϣ����" & Chr(13) & Chr(10)
                txtMsg.Text = txtMsg.Text + comPort.Text + "�˿��Ѵ�" + Chr(13) + Chr(10)
                txtMsg.Text = txtMsg.Text + "ͨ�Ų���Ϊ��" + Chr(13) + Chr(10)
                txtMsg.Text = txtMsg.Text + baud & "," & parity & "," & numBit & "," & stopbit + Chr(13) + Chr(10)
                btnOpenSerial.Caption = "�رմ���"
                shpSerial.FillColor = &HFF00&
            End If
        Else
            txtMsg.Text = "��Ϣ����" & Chr(13) & Chr(10)
            txtMsg.Text = txtMsg.Text + "ͨ�Ų���������" + Chr(13) + Chr(10)
            MsgBox "ͨ�Ų���������", vbOKOnly, "��Ϣ"
            GoTo Label1
        End If
    '�رմ���
    ElseIf btnOpenSerial.Caption = "�رմ���" Then
        MSComm1.PortOpen = False
        shpSerial.FillColor = &HFF&
        txtMsg.Text = "��Ϣ����" & Chr(13) & Chr(10)
        txtMsg.Text = txtMsg.Text + "�˿��ѹر�" + Chr(13) + Chr(10)
        btnOpenSerial.Caption = "�򿪴���"
    End If
Label1:
End Sub


Private Sub btnSend_Click_Click()
    On Error Resume Next
    If Trim(txtSend.Text) = "" Or Trim(txtSend.Text) = "��������" + Chr(13) + Chr(10) Then
        txtMsg.Text = txtMsg.Text + "�����뷢������" + Chr(13) + Chr(10)
        MsgBox "�����뷢������", vbOKOnly, "��Ϣ"
        Exit Sub
    End If
        'txtSend.Text = Replace(txtSend.Text, "��������" + Chr(13) + Chr(10), "")
        MSComm1.Output = Trim(txtSend.Text)
        txtMsg.Text = txtMsg.Text + txtSend.Text + Chr(13) + Chr(10)
        'Dim str() As Byte
        Dim st0 As String
        Dim st1() As Byte
        'str = StrConv(txtMsg.Text, vbFromUnicode)
        st1() = txtMsg.Text
        st0 = Hex(st1(0)) + Hex(st1(2))
        Text6.Text = st0
    If Err.Number = 8018 Then
        txtMsg.Text = txtMsg.Text & "����δ��" & Chr(13) & Chr(10)
    End If
End Sub

Private Sub Check1_Click()
    If Check1.Value Then
        MSComm1.InputMode = comInputModeBinary
    Else
        MSComm1.InputMode = comInputModeText
    End If
End Sub




Private Sub Command1_Click()
    Text1.Text = ""
    Text2.Text = ""
    Text3.Text = ""
    Text4.Text = ""
    Text5.Text = ""
    Text12.Text = ""
End Sub

Private Sub Command10_Click()
    Set conn0 = New ADODB.Connection
    Set rs0 = New ADODB.Recordset
    
    conn0.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;" & _
                   "Data Source=" & App.Path & "\DBEmp.mdb;" & _
                   "Persist security Info=False"
    conn0.Open
    rs0.Open "select * from Phone where ��ϵ��ʽ='" & _
        MSHFlexGrid2.TextMatrix(MSHFlexGrid2.Row, 1) & "'", _
        conn0, adOpenKeyset, adLockOptimistic
'    rs.Open "EmpTable", conn, , adCmdTable
'    rs.MoveLast

    rs0.Delete
    rs0.Update
    rs0.Clone
    conn0.Close
    
    Reshow0
End Sub

Private Sub Command11_Click()
    Set conn0 = New ADODB.Connection
    Set rs0 = New ADODB.Recordset
    
    conn0.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;" & _
                   "Data Source=" & App.Path & "\DBEmp.mdb;" & _
                   "Persist security Info=False"
    conn0.Open
    rs0.Open "select * from Phone where ��ϵ��ʽ='" & _
        MSHFlexGrid2.TextMatrix(MSHFlexGrid2.Row, 1) & "'", _
        conn0, adOpenKeyset, adLockOptimistic

    rs0.Fields(0) = Text3.Text

    rs0.Update
    rs0.Clone
    conn0.Close
    
    Reshow0
End Sub

Private Sub Command12_Click()
    Text10.Text = Now
    
    On Error Resume Next
        MSComm1.Output = Trim(("+B " + Text10.Text + Chr(10)))
        waittime (1)
        txtMsg.Text = txtMsg.Text + ("+B " + Text10.Text + Chr(10)) + Chr(13) + Chr(10)
    If Err.Number = 8018 Then
        txtMsg.Text = txtMsg.Text & "����δ��" & Chr(13) & Chr(10)
    End If
End Sub

Private Sub Command13_Click()
    Reshow
    Reshow0
    Dim v
    For v = 1 To (MSHFlexGrid1.Rows - 1)
        SlaveNum.AddItem (v)
    Next v
    
    comPort.ListIndex = 0
End Sub

Private Sub Command2_Click()
    On Error Resume Next
        MSComm1.Output = Trim(("+A " + Text5.Text + Text3.Text + Text4.Text + Chr(10)))
        txtMsg.Text = txtMsg.Text + ("+A " + Text5.Text + Text3.Text + Text4.Text + Chr(10)) + Chr(13) + Chr(10)
    If Err.Number = 8018 Then
        txtMsg.Text = txtMsg.Text & "����δ��" & Chr(13) & Chr(10)
    End If
    
    Set conn = New ADODB.Connection
    Set rs = New ADODB.Recordset
    
    
    conn.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;" & _
                   "Data Source=" & App.Path & "\DBEmp.mdb;" & _
                   "Persist security Info=False"
    conn.Open
    
    Dim sqlDel1  As String
    sqlDel1 = "delete * from EmpTable"
    conn.Execute (sqlDel1)
    
    rs.Update
    rs.Close
    conn.Close
    
    Reshow
End Sub

Private Sub Command3_Click()


'    On Error Resume Next
'        MSComm1.Output = Trim(("+D " + Text1.Text + Text2.Text + Chr(10)))
'        txtMsg.Text = txtMsg.Text + ("+D " + Text1.Text + Text2.Text + Chr(10)) + Chr(13) + Chr(10)
'    If Err.Number = 8018 Then
'        txtMsg.Text = txtMsg.Text & "����δ��" & Chr(13) & Chr(10)
'    End If
    

    Set conn = New ADODB.Connection
    Set rs = New ADODB.Recordset
    
    
    conn.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;" & _
                   "Data Source=" & App.Path & "\DBEmp.mdb;" & _
                   "Persist security Info=False"
    conn.Open
    rs.Open "select * from EmpTable", conn, , adCmdTable

    rs.AddNew
    rs.Fields(0).Value = Text1.Text
    rs.Fields(1).Value = Text2.Text
    
    rs.Update
    rs.Close
    conn.Close
    
    Reshow
End Sub

Private Sub Command4_Click()
Reshow
Reshow0
End Sub

Private Sub Command5_Click()
If Command5.Caption = "�������" Then
Command5.Caption = "�˳�����"
Shape2.FillColor = &HFF00&
Dim strsla
strsla = SlaveNum
    On Error Resume Next
        MSComm1.Output = Trim(("+G " + strsla + Chr(10)))
        txtMsg.Text = txtMsg.Text + ("+G " + strsla + Chr(10)) + Chr(13) + Chr(10)
    If Err.Number = 8018 Then
        txtMsg.Text = txtMsg.Text & "����δ��" & Chr(13) & Chr(10)
    End If
Else
Shape2.FillColor = &HFF&
Command5.Caption = "�������"
End If
End Sub

Private Sub Command6_Click()
    On Error Resume Next
        MSComm1.Output = Trim(("+F " + Text5.Text + Text12.Text + Text4.Text + Chr(10)))
        waittime (1)
        txtMsg.Text = txtMsg.Text + ("+F " + Text5.Text + Text3.Text + Text4.Text + Chr(10)) + Chr(13) + Chr(10)
    If Err.Number = 8018 Then
        txtMsg.Text = txtMsg.Text & "����δ��" & Chr(13) & Chr(10)
    End If
    
    
 '   MsgBox (MSHFlexGrid1.Rows - 1)
        Dim i
        For i = 1 To (MSHFlexGrid1.Rows - 1)
        
         On Error Resume Next
            MSComm1.Output = Trim(("+D " + MSHFlexGrid1.TextMatrix(i, 1) + MSHFlexGrid1.TextMatrix(i, 2) + Chr(10)))
            txtMsg.Text = txtMsg.Text + ("+D " + MSHFlexGrid1.TextMatrix(i, 1) + MSHFlexGrid1.TextMatrix(i, 2) + Chr(10))
         waittime (1)
         If Err.Number = 8018 Then
             txtMsg.Text = txtMsg.Text & "����δ��" & Chr(13) & Chr(10)
            End If
        Next i
       
       
       Dim j
       For j = 1 To (MSHFlexGrid2.Rows - 1)
         On Error Resume Next
            MSComm1.Output = Trim(("+B " + MSHFlexGrid2.TextMatrix(j, 1) + Chr(10)))
            txtMsg.Text = txtMsg.Text + ("+B " + MSHFlexGrid2.TextMatrix(j, 1) + Chr(10))
         waittime (1)
         If Err.Number = 8018 Then
             txtMsg.Text = txtMsg.Text & "����δ��" & Chr(13) & Chr(10)
            End If
        Next j
     
    
End Sub

Private Sub Command7_Click()

'    On Error Resume Next
'        MSComm1.Output = Trim(("+E " + Text5.Text + Text3.Text + Text4.Text + Chr(10)))
'        txtMsg.Text = txtMsg.Text + ("+E " + Text5.Text + Text3.Text + Text4.Text + Chr(10)) + Chr(13) + Chr(10)
'    If Err.Number = 8018 Then
'        txtMsg.Text = txtMsg.Text & "����δ��" & Chr(13) & Chr(10)
'    End If
    

    Set conn = New ADODB.Connection
    Set rs = New ADODB.Recordset
    
    conn.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;" & _
                   "Data Source=" & App.Path & "\DBEmp.mdb;" & _
                   "Persist security Info=False"
    conn.Open
    rs.Open "select * from EmpTable where �ֻ���ַ='" & _
        MSHFlexGrid1.TextMatrix(MSHFlexGrid1.Row, 2) & "'", _
        conn, adOpenKeyset, adLockOptimistic
'    rs.Open "EmpTable", conn, , adCmdTable
'    rs.MoveLast

    rs.Delete
    rs.Update
    rs.Clone
    conn.Close
    
    Reshow
End Sub

Private Sub Command8_Click()


'    On Error Resume Next
'        MSComm1.Output = Trim(("+F " + Text5.Text + Text3.Text + Text4.Text + Chr(10)))
'        txtMsg.Text = txtMsg.Text + ("+C " + Text5.Text + Text3.Text + Text4.Text + Chr(10)) + Chr(13) + Chr(10)
'    If Err.Number = 8018 Then
'        txtMsg.Text = txtMsg.Text & "����δ��" & Chr(13) & Chr(10)
'    End If
    
    Set conn = New ADODB.Connection
    Set rs = New ADODB.Recordset
    
    conn.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;" & _
                   "Data Source=" & App.Path & "\DBEmp.mdb;" & _
                   "Persist security Info=False"
    conn.Open
    rs.Open "select * from EmpTable where �ֻ���ַ='" & _
        MSHFlexGrid1.TextMatrix(MSHFlexGrid1.Row, 2) & "'", _
        conn, adOpenKeyset, adLockOptimistic

    rs.Fields(0) = Text1.Text
    rs.Fields(1) = Text2.Text
    rs.Update
    rs.Clone
    conn.Close
    
    Reshow
End Sub




Private Sub Command9_Click()

    Set conn0 = New ADODB.Connection
    Set rs0 = New ADODB.Recordset
    
    
    conn0.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;" & _
                   "Data Source=" & App.Path & "\DBEmp.mdb;" & _
                   "Persist security Info=False"
    conn0.Open
    rs0.Open "select * from Phone where ��ϵ��ʽ='" & Text3.Text & "'", conn0, 1, adCmdTable
    rs0.AddNew
    rs0.Fields(0).Value = Text3.Text
    
    If rs0.RecordCount > 0 Then
        MsgBox "�Ѿ�����"
    Exit Sub
    End If
    
    
    rs0.Update
    
    rs0.Close
    conn0.Close
    
    Reshow0

    
    
End Sub
Private Sub Form_load()
    
    comPort.ItemData(0) = 1
    comPort.ItemData(1) = 2
    comPort.ItemData(2) = 3
    comPort.ItemData(3) = 4
    comPort.ItemData(4) = 5
    comPort.ItemData(5) = 6
    comPort.ItemData(6) = 7
    comPort.ItemData(7) = 8
    
    comPort.ListIndex = 0
    
    shpSerial.FillColor = &HFF&
    Shape2.FillColor = &HFF&
    
    txtMsg.Text = "��Ϣ����" & Chr(13) & Chr(10)
    txtReceive.Text = "��������" & Chr(13) & Chr(10)
    txtSend.Text = "��������" & Chr(13) & Chr(10)
    

    MSHFlexGrid1.FormatString = "|�ֻ����|�ֻ���ַ"
    MSHFlexGrid1.FormatString = ";| 1"
    MSHFlexGrid1.ColWidth(0) = 500
    MSHFlexGrid1.ColWidth(2) = 6501
    MSHFlexGrid1.RowHeight(0) = 400
    MSHFlexGrid1.RowHeight(1) = 300
    'Reshow
    
    
    MSHFlexGrid2.FormatString = "|��ϵ��ʽ"
    MSHFlexGrid2.FormatString = ";| 1"
    MSHFlexGrid2.ColWidth(0) = 500
    MSHFlexGrid2.ColWidth(1) = 2000
    MSHFlexGrid2.RowHeight(0) = 400
    MSHFlexGrid2.RowHeight(1) = 300
    
                   
End Sub

Private Sub MSComm1_OnComm()
    Dim buf As String
    Dim InData As Variant ' �������
    Dim Arr(0) As Byte    ' �����ֽ�����
    Select Case MSComm1.CommEvent
            Case comEvReceive ' ���������¼�
    'InData = MSComm1.Input ' ��������
    buf = MSComm1.Input
    'Arr(0) = AscB(InData)       ' ����ת��
    'txtReceive.Text = txtReceive.Text + Arr(0)    ' ��ʾ����
    MSComm1.InBufferCount = 0 ' ��ս��ջ�
    txtReceive.Text = txtReceive.Text & buf
    End Select
End Sub



Private Sub txtSend_Change()
    txtMsg.SelStart = Len(txtMsg.Text)
End Sub
Private Sub waittime(delay As Single)
Dim starttime As Single
starttime = Timer
Do Until (Timer - starttime) > delay
DoEvents
Loop
End Sub

function varargout = Computer_Program(varargin)
% COMPUTER_PROGRAM M-file for Computer_Program.fig
%      COMPUTER_PROGRAM, by itself, creates a new COMPUTER_PROGRAM or raises the existing
%      singleton*.
%
%      H = COMPUTER_PROGRAM returns the handle to a new COMPUTER_PROGRAM or the handle to
%      the existing singleton*.
%
%      COMPUTER_PROGRAM('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in COMPUTER_PROGRAM.M with the given input arguments.
%
%      COMPUTER_PROGRAM('Property','Value',...) creates a new COMPUTER_PROGRAM or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Computer_Program_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Computer_Program_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Copyright 2002-2003 The MathWorks, Inc.

% Edit the above text to modify the response to help Computer_Program

% Last Modified by GUIDE v2.5 24-Oct-2003 22:30:15

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Computer_Program_OpeningFcn, ...
                   'gui_OutputFcn',  @Computer_Program_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before Computer_Program is made visible.
function Computer_Program_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Computer_Program (see VARARGIN)

% Choose default command line output for Computer_Program
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);


% UIWAIT makes Computer_Program wait for user response (see UIRESUME)
% uiwait(handles.figure1);
clear all
clc
global a;
a=serial('COM1','BAUDRATE',9600);
% --- Outputs from this function are returned to the command line.
function varargout = Computer_Program_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in Forward.
function Forward_Callback(hObject, eventdata, handles)
% hObject    handle to Forward (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of Forward
global a;
state=get(hObject,'Value');
if(state==1)
    fopen(a);
    disp('State:  Started Moving Forward');
    fwrite(a,1);
    fclose(a);
end
if(state==0)
    fopen(a);
    disp('State:  Stopped Moving Forward');
    fwrite(a,0);
    fclose(a);
end



% --- Executes on button press in backward.
function backward_Callback(hObject, eventdata, handles)
% hObject    handle to backward (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of backward
global a;
state=get(hObject,'Value');
if(state==1)
    fopen(a);
    disp('State:  Started Moving Backward');
    fwrite(a,2);
    fclose(a);
end
if(state==0)
    fopen(a);
    disp('State:  Stopped Moving Backward');
    fwrite(a,0);
    fclose(a);
end


% --- Executes on button press in left.
function left_Callback(hObject, eventdata, handles)
% hObject    handle to left (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of left
global a;
state=get(hObject,'Value');
if(state==1)
    fopen(a);
    disp('State:  Started Moving Left');
    fwrite(a,3);
    fclose(a);
end
if(state==0)
    fopen(a);
    disp('State:  Stopped Moving Left');
    fwrite(a,0);
    fclose(a);
end

% --- Executes on button press in right.
function right_Callback(hObject, eventdata, handles)
% hObject    handle to right (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of right
global a;
state=get(hObject,'Value');
if(state==1)
    fopen(a);
    disp('State:  Started Moving Right');
    fwrite(a,4);
    fclose(a);
end
if(state==0)
    fopen(a);
    disp('State:  Stopped Moving Right');
    fwrite(a,0);
    fclose(a);
end



% --- Executes during object creation, after setting all properties.
function axes2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes2




% --- Executes on button press in togglebutton8.
% --- Executes during object creation, after setting all properties.
function axes3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes3



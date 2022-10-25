import http
from http.client import HTTPResponse
from msilib.schema import Error
from django.shortcuts import render

from server.serializers import (
    createPersonSerializer,
    createListSerializer,
    listPersonSerializer,
    updateListSerializer,
    listListSerializer,
)
from rest_framework.generics import ListAPIView, CreateAPIView, RetrieveUpdateAPIView
from .models import Person, Items_listed

# Create your views here.


class personCreateAPIView(CreateAPIView):
    queryset = Person.objects.all()
    serializer_class = createPersonSerializer


class personListAPIView(ListAPIView):
    serializer_class = listPersonSerializer
    #queryset = Person.objects.all()

    def get_queryset(self, *args, **kwargs):
        rec_email = self.kwargs.get('email')
        rec_password = self.kwargs.get('password')
        curr = Person.objects.filter(email=rec_email)
        if(curr.count() == 0):
            return HTTPResponse("User Doesn't Exist")
        if(curr.password == rec_password):
            return curr[0]
        return HTTPResponse("Wrong Password")


class itemListAPIView(ListAPIView):
    serializer_class = listListSerializer
    #queryset = Items_listed.objects.all()

    def get_queryset(self, *args, **kwargs):
        id = self.kwargs.get('id')
        persons = Person.objects.filter(Aadhar_id=id)[0]
        return Items_listed.objects.filter(lender_id=persons)


class itemCreateAPIView(CreateAPIView):
    queryset = Items_listed.objects.all()
    serializer_class = createListSerializer


class itemUpdateAPIView(RetrieveUpdateAPIView):
    queryset = Items_listed.objects.all()
    serializer_class = updateListSerializer
    lookup_field = 'status'


# from django.shortcuts import render
# from django.db import connection
# from rest_framework.response import Response
# from rest_framework.decorators import api_view
# from .serializers import ItemSerializer, Person
# from .models import Person, Items_listed, borrower
#
# @api_view(['GET'])
# def getData(request):
#     personal_data= Person.objects.get()
#     serializer= ItemSerializer(personal_data)
#     return Response(serializer.data)
#
# # Create your views here.
# from django.http import HttpResponse
#
#
# def index(request):
#     return HttpResponse("Hello, world. You're at the polls index.")
#
# def home(request):
#     return render(request,'home')
#
# #@login_required
# def personal_info(request):
#     if request.method=="POST":
#         form = Person(request.POST)
#         if form.is_valid():
#             details= Person(id= request.Aadhar_id, name=request.name, address= request.address, phone= request.phone_no)
#             details.save();
#             messages.success(request, f"New User Created")
#        # else:
#         #    form =
#
#
# def items_posted(request):
#     if request.method=="POST":
#         form = Items_listed(request.POST)
#         if form.is_valid():
#             details= Items_listed(id= request.Aadhar_id, name=request.name, address= request.address, phone= request.phone_no)
#             details.save();
#             messages.success(request, f"New User Created")
#         #else:
#          #   form =
#
#
# def customer(request):
#     with connection.cursor() as cursor:
#         query= "SELECT Aadhar_id,email,name, address, phone_no FROM Person where lender_id= user.request.Aadhar_id"
#         cursor.execute(query)
#         row = cursor.fetchone()
#
#
#
# def seller(reqest):
#     with connection.cursor() as cursor:
#         query= "SELECT item_id,name, description FROM Items_listed where lender_id= user.request.Aadhar_id"
#         cursor.execute(query)
#         row = cursor.fetchone()
#         all_count, yes_count = row
#
# def items_available(reqest):
#     with connection.cursor() as cursor:
#         query= "SELECT item_id,name, description, loaction, price status FROM Items_listed"
#         cursor.execute(query)
#         row = cursor.fetchone()
#         all_count, yes_count = row
#
#
# def borrowed(reqest):
#     with connection.cursor() as cursor:
#         query= "SELECT item_id,name, borrow_date, return_date, amount FROM borrower where borrow_id= user.request.Aadhar_id"
#         cursor.execute(query)
#         row = cursor.fetchone()
#         all_count, yes_count = row
#
#
# def itembyname(request):
#     with connection.cursor() as cursor:
#         query= "SELECT borrower.item_id, name, amount, FROM borrower,Items_listed where name=user.request.name AND borrower.item_id=Items_listed.item_id"
#         cursor.execute(query)
#         row = cursor.fetchone()
#         all_count, yes_count = row
#
#
#
#

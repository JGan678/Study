from multiprocessing import context
from django.shortcuts import render
from .models import *


def index(request):
    return "Hello, world. You're at the polls index."


def input(request):
    render(request, 'input.html', context)

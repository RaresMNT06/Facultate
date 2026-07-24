cmake_minimum_required(VERSION 4.1)
project(Lab3_5 C)

set(CMAKE_C_STANDARD 11)


add_executable(Lab3_5
        main.c
        domain/participant.c
        domain/participant.h
        repo/repo_participant.c
        repo/repo_participant.h
        service/service_participant.c
        service/service_participant.h
        ui/ui.c
        ui/ui.h
        teste/teste_domain.c
        teste/teste_repo.c
        teste/teste_service.c)


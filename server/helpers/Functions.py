def generator(response, source='Python API', status=True, errorcode=None, errormessage=None):
    return {'provider': {'source': source}, 'response': response,
            'status': status, 'error': {'code': errorcode, 'message': errormessage}}
from string import ascii_letters

def MaxPrefix(v, step, mx):

    prefix = ''

    for c in ascii_letters:
        v1 = []
        
        for j in range(len(v)):
            if len(v[j]) > step:
                if v[j][step] == c:
                    v1.append(v[j])
               
        if len(v1) >= 2:
            mx_aux, prefix_aux = MaxPrefix(v1, step + 1, mx)
            if mx_aux > mx:
                mx = mx_aux
                prefix = prefix_aux
        else:
            if step > mx:
                mx = step
                prefix = v[0][:step]
              
    return mx, prefix

def longestPreix(arr):
    n = 0
    try: 
        if len(arr) < 1: return ''
        elif len(arr) == 1: return arr[0]
        n = min(map(lambda x: len(x), arr))
    except: return ''

    prefix = []
    for i in range(n):
        for s in arr[1:]:
            if s[i] != arr[0][i]:
                return prefix
        prefix.append(arr[0][i])
    return prefix

# Driver code
if __name__ == '__main__':
      
    # Initialising strings 
    s1 = ['c', 'd', 'e']
    s2 = ['a', 'B', 'c', 'x']
    s3 = ['a', 'B', 'c', 'a']
    s4 = ['a', 'b', 'c', 'a', 'e']
    v = []
  
    # Push strings into vectors.
    v.append(s1)
    v.append(s2)
    v.append(s3)
    v.append(s4)
      
    print(MaxPrefix(v, 0, 0))
    print(longestPreix(v))
    print(['a', 'B', 'c', 'a'] == ['a', 'B', 'c', 'a'])
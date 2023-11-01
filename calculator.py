n = input("input:")
postorder = []          
operater_stack = []
top = -1

#Give the operator priority.
def priority(i):            
    if i == "*" or i == "/":
        result = 2
    else:
        result = 1

    return result

#Store the n to as list.
formula = []
s = ""
for i in range(len(n)):
    if n[i] == "+" or n[i] == "-" or n[i] == "*" or n[i] == "/":
        if s != "" :
            formula.append(s)
        formula.append(n[i])
        s = ""
    else:
        s += n[i]
formula.append(s)

#Scan the list and seperate them from operator to operand.
for i in formula:           
    if i != "*" and i != "/" and i != "+" and i != "-":
        postorder.append(i)

    elif operater_stack == []:
        operater_stack.append(i)
        top += 1

    #Compare their priority of operator.
    elif priority(i) > priority(operater_stack[top]):           
        operater_stack.append(i)
        top += 1

    elif priority(i) <= priority(operater_stack[top]):
        while True:
            if top == -1 or priority(i) > priority(operater_stack[top]):
                operater_stack.append(i)
                top += 1 
                break

            else:
                postorder.append(operater_stack[top])
                operater_stack.pop(top)
                top -= 1
                
#Output the operator left.
for i in range(top ,-1 ,-1):   
    postorder.append(operater_stack[i])
    operater_stack.pop(i)

#Transform every data's type from string to integer except operator.
for i in postorder:
    if i != "+" and i != "-" and i != "*" and i != "/":
        postorder[postorder.index(i)] = int(i)

#Use the postorder to calculate the answer of the formula. 
k = -1
while k + 1 < len(postorder):
    k += 1
    if postorder[k] == "+":
        postorder[k-2] = postorder[k-2] + postorder[k-1]

    elif postorder[k] == "-":
        postorder[k-2] = postorder[k-2] - postorder[k-1]

    elif postorder[k] == "*":
        postorder[k-2] = postorder[k-2] * postorder[k-1]

    elif postorder[k] == "/":
        postorder[k-2] = postorder[k-2] / postorder[k-1]
    else:
        continue
    postorder.pop(k)
    postorder.pop(k-1)
    k -= 2

print("answer:" ,postorder[0])
#end

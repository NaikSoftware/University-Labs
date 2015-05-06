import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

import static java.lang.System.out;

public class Main {

	public static final boolean d = false;

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		out.println("Please input expression for open");
		String expr = scanner.next();
		scanner.close();
		out.println("INPPUT EXPR = " + expr);

		String result = expr, last_result = expr;
		while (!(result = openBrackets(result)).equals(last_result)) {
			out.println();
			out.println(" = " + result);
			last_result = result;
		}
		out.println();
		out.println("Result:" + result.replace("+", " + "));
	}

	public static String openBrackets(String expr) {
		int ind_to_two = expr.indexOf('(', 1);
		if (ind_to_two == -1)
			return expr;

		String one = expr.substring(1, ind_to_two - 1);
		int ind_end_two = expr.indexOf(')', ind_to_two);
		String two = expr.substring(ind_to_two + 1, ind_end_two);
		if (d) {
			out.println("One:" + one);
			out.println("Two:" + two);
		}

		String mult = mult(one, two);
		mult = removeDuplicatesImpl(mult);
		String last = mult;
		while (!(mult = absorb(mult)).equals(last)) {
			last = mult;
		}
		expr = expr.replace(one, mult);
		expr = expr.replace("(" + two + ")", "");

		return expr;
	}

	private static String absorb(String expr) {
		String[] implicates = expr.split("\\+");
		ArrayList<String> cleared_impl = new ArrayList<String>();
		cleared_impl.addAll(Arrays.asList(implicates));
		String absorbed = null;

		for (String impl : implicates) {
			boolean absorb = false;
			for (String impl2 : implicates) {
				if (implBcontainA(impl, impl2)) {
					ArrayList<String> a_vars = splitImpl(impl);
					ArrayList<String> b_vars = splitImpl(impl2);
					if (b_vars.size() - a_vars.size() == 1) {
						if (d) out.println("\tdetected absorb");
						absorbed = impl2;
						absorb = true;
						break;
					}
				}
				if (absorb)
					break;
			}
			if (absorb) {
				if (d) out.println("remove " + absorbed);
				cleared_impl.remove(absorbed);
			}
		}
		String resultExpr = "";
		for (String impl : cleared_impl) {
			resultExpr += (impl + "+");
		}
		if (resultExpr.isEmpty())
			return resultExpr;
		return resultExpr.substring(0, resultExpr.length() - 1);
	}

	private static String removeDuplicatesImpl(String expr) {
		String[] implicates = expr.split("\\+");
		ArrayList<String> cleared_impl = new ArrayList<String>();

		for (String impl : implicates) {
			boolean match = false;
			for (String impl2 : cleared_impl) {
				if (impl_equals(impl, impl2)) {
					// out.println("match detected " + impl + "==" + impl2);
					match = true;
					break;
				}
			}
			if (!match)
				cleared_impl.add(impl);
			else {
				// if (d) out.println("skipped " + impl);
			}
		}
		String resultExpr = "";
		for (String impl : cleared_impl) {
			resultExpr += (impl + "+");
		}
		if (resultExpr.isEmpty())
			return resultExpr;
		return resultExpr.substring(0, resultExpr.length() - 1);
	}

	private static boolean impl_equals(String a, String b) {
		return a.length() == b.length() && implBcontainA(a, b);
	}

	private static boolean implBcontainA(String a, String b) {
		if (a == b || a.equals(b))
			return true;
		ArrayList<String> a_vars = splitImpl(a);
		ArrayList<String> b_vars = splitImpl(b);
		for (String a_var : a_vars) {
			if (!b_vars.contains(a_var))
				return false;
		}
		return true;
	}

	private static String mult(String one, String two) {
		String result = "";
		String[] one_arr = one.split("\\+");
		String[] two_arr = two.split("\\+");
		for (int i = 0; i < one_arr.length; i++) {
			for (int j = 0; j < two_arr.length; j++) {
				if (one_arr[i].equals(two_arr[j])) {
					result += (one_arr[i] + "+");// ?
				} else if (reduced(String.valueOf(one_arr[i]) + two_arr[j])) {
					// skip
				} else {
					String impl = one_arr[i] + two_arr[j];
					impl = removeDuplicateVars(impl);
					result += (impl + "+");
				}
			}
		}
		if (result.endsWith("+")) {
			result = result.substring(0, result.length() - 1);
		}
		return result;
	}

	private static String removeDuplicateVars(String impl) {
		ArrayList<String> vars = splitImpl(impl);
		ArrayList<String> cleared_vars = new ArrayList<String>();
		for (String var : vars) {
			if (!cleared_vars.contains(var)) {
				cleared_vars.add(var);
			}
		}
		String resultImpl = "";
		for (String var : cleared_vars) {
			resultImpl += var;
		}
		return resultImpl;
	}

	/**
	 * 
	 * @param impl импликанта
	 * @return true если импликанта самосокращается (например 1!1, 12!1)
	 */
	private static boolean reduced(String impl) {
		ArrayList<String> vars = splitImpl(impl);
		for (String var : vars) {
			if (var.contains("!")) {
				if (vars.contains(var.replace("!", ""))) {
					return true;
				}
			} else {
				if (vars.contains("!" + var)) {
					return true;
				}
			}
		}
		return false;
	}

	// Split to variables
	private static ArrayList<String> splitImpl(String impl) {
		ArrayList<String> vars = new ArrayList<String>();
		char[] chars = impl.toCharArray();
		for (int i = 0; i < chars.length; i++) {
			if (chars[i] == '!') {
				vars.add("!" + chars[i + 1]);
				i++;
			} else {
				vars.add(String.valueOf(chars[i]));
			}
		}
		return vars;
	}

}
